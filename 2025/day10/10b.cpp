#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;
const double EPS = 1e-9;


double operator*(const vector<double>& a, const vector<double>& b)
{
    double result = 0;
    for (int i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

double operator*(const vector<double>& a, const vector<int>& b)
{
    double result = 0;
    for (int i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

vector<double> operator*(const vector<double>& a, double b)
{
    vector<double> result = a;
    for (double & e: result)
        e *= b;
    return result;
}

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
    vector<double> result = a;
    for (int i = 0; i < a.size(); ++i)
        result[i] += b[i];
    return result;
}

vector<double> operator/(const vector<double>& a, double b)
{
    vector<double> result = a;
    for (double & e: result)
        e /= b;
    return result;
}

bool operator>=(const vector<double>& a, double b)
{
    for (double e : a)
        if (e < b)
            return false;
    return true;
}

vector<double> get_column(int c, const vector<vector<double>>& m)
{
    vector<double> result;
    for (int i = 0; i < m.size(); ++i)
        result.push_back(m[i][c]);
    return result;
}

void delete_column(vector<vector<double>>& m, int c)
{
    for (int i = 0; i < m.size(); ++i)
        m[i].erase(m[i].begin() + c);
}

int get_index(int val, const vector<int>& a)
{
    for (int i = 0; i < a.size(); ++i)
        if (a[i] == val)
            return i;
    return -1;
}



class Simplex
{
private:
    int sol_vars;
    int extra_vars;
    int num_const;
    vector<int> goal_func;
    vector<vector<int>> constraints;
    vector<int> const_signs; // 1: <=, 0: =, -1: >=
    vector<vector<double>> tableau;
    vector<int> artf_vars;
    vector<int> base_vars;
    bool feas, unb;
    vector<double> solution;


    void normalize_constraints()
    {
        for (int i = 0; i < num_const; ++i)
        {
            if (const_signs[i] == -1)
            {
                // Add surplus variable
                for (int j = 0; j < num_const; ++j)
                    constraints[j].insert(constraints[j].end() - 1, (i == j) ? -1 : 0);
                ++extra_vars;
                goal_func.push_back(0);
                const_signs[i] = 0;
            }
        }
    }

    void sanitize_tableau()
    {
        for (int i = 0; i < tableau.size(); ++i)
            for (int j = 0; j < tableau[0].size(); ++j)
                if (fabs(tableau[i][j] - round(tableau[i][j])) < EPS)
                    tableau[i][j] = round(tableau[i][j]);
    }

    bool stop_condition(int row)
    {
        for (int i = 0; i < tableau[0].size()-1; ++i)
        {
            if (tableau[row][i] < -EPS)
                return false;
        }
        return true;
    }

    void initialize_problem()
    {
        tableau = vector<vector<double>>(num_const + 2, vector<double>(sol_vars + extra_vars + num_const + 1, 0));
        // Constraints part
        for (int i = 0; i < num_const; ++i)
        {
            // Copy constraints
            for (int j = 0; j < sol_vars + extra_vars; ++j)
                tableau[i][j] = constraints[i][j];
            // Fill slack / artificial variables part of tableau
            tableau[i][sol_vars + extra_vars + i] = 1;
            // Add 0 coef to goal_func
            goal_func.push_back(0);
            // Add variable to base variables
            base_vars.push_back(sol_vars + extra_vars + i);
            // Add variable to artf_variables list if artificial
            if (const_signs[i] == 0)
                artf_vars.push_back(sol_vars + extra_vars + i);
            tableau[i].back() = constraints[i].back(); // Right-hand side
        }
        // Goal function row for phase I (w)
        vector<int> w_func = vector<int>(tableau[0].size()-1, 0);
        for (int v : artf_vars)
            w_func[v] = 1;
        // Fill last two rows (w and z)
        vector<int> wcb, zcb = vector<int>();
        for (int v : base_vars)
        {
            wcb.push_back(w_func[v]);
            zcb.push_back(goal_func[v]);
        }
        for (int i = 0; i < tableau[0].size()-1; ++i)
        {
            vector<double> yi = get_column(i, tableau);
            tableau[tableau.size()-2][i] = w_func[i] - yi*wcb;
            tableau.back()[i] = goal_func[i] - yi*zcb;
        }
        vector<double> yi = get_column(tableau[0].size()-1, tableau);
        tableau[tableau.size()-2].back() = -(yi*wcb);
        tableau.back().back() = -(yi*zcb);
    }

    void pivot(int enter, int out)
    {
        // Pivot
        double pivot = tableau[out][enter];
        tableau[out] = tableau[out] / pivot;
        for (int i = 0; i < tableau.size(); ++i)
        {
            if (i != out)
            {
                double factor = tableau[i][enter];
                tableau[i] = tableau[i] + (tableau[out] * (-factor));
            }
        }
        // Update base variables
        base_vars[out] = enter;
        sanitize_tableau();
    }

    void remove_artificial_variables()
    {
        // Order from highest to lowest to avoid extra index issues when deleting columns
        sort(artf_vars.begin(), artf_vars.end(), greater<int>());
        for (int v : artf_vars)
        {
            // Check if artificial variable is in basis
            int row = get_index(v, base_vars);
            if (row != -1) // Artificial variable is in basis, but is 0
            {
                // Check if restriction is redundant
                bool redundant = true;
                for (int i = 0; i < tableau[0].size()-1; ++i)
                {
                    if (get_index(i,artf_vars) == -1 && fabs(tableau[row][i]) > EPS)
                    {
                        redundant = false;
                        break;
                    }
                }
                // If redundant, can be directly removed
                if (redundant)
                {
                    // Remove row
                    tableau.erase(tableau.begin() + row);
                    // One less restriction
                    --num_const;
                    // Update base
                    base_vars.erase(base_vars.begin() + row);
                }
                // If not redundant, must be pivoted out
                else
                {
                    // Find non-artificial and non-basic variable to pivot in
                    int enter = -1;
                    for (int i = 0; i < tableau[0].size()-1; ++i)
                    {
                        if (get_index(i, artf_vars) == -1 && get_index(i, base_vars) == -1 && fabs(tableau[row][i]) > EPS)
                        {
                            enter = i;
                            break;
                        }
                    }
                    if (enter != -1)
                        pivot(enter, row);
                }
            }
            // Remove column
            delete_column(tableau, v);
            for (int & b : base_vars)
                if (b > v)
                    --b;
        }
    }

    bool solve_phase_one()
    {
        // Loop until stopping condition: all coefs in w >= 0 or no viable pivots
        vector<int> discarded_enters;
        while (!stop_condition(tableau.size()-2))
        {
            // Determine entering variable (most negative)
            int enter = -1;
            double min_coef = -EPS;
            for (int i = 0; i < tableau[0].size()-1; ++i)
            {
                if (tableau[tableau.size()-2][i] < min_coef && get_index(i, discarded_enters) == -1)
                {
                    min_coef = tableau[tableau.size()-2][i];
                    enter = i;
                }
            }
            // If there is no enter variable, stop the process
            if (enter == -1)
                break;
            // Determine leaving variable (minimum ratio test)
            int out = -1;
            double min_ratio;
            for (int i = 0; i < num_const; ++i)
            {
                if (tableau[i][enter] > EPS)
                {
                    double ratio = tableau[i].back() / tableau[i][enter];
                    if (out == -1 || ratio < min_ratio)
                    {
                        min_ratio = ratio;
                        out = i;
                    }
                }
            }
            // If no leaving variable found, discard entering variable and search again
            if (out == -1)
                discarded_enters.push_back(enter);
            // Else, pivot
            else
            {
                pivot(enter, out);
                discarded_enters.clear();
            }
        }
        // Check feasibility: w = 0
        bool feasibility = (fabs(tableau[tableau.size()-2].back()) < EPS);
        if (feasibility)
        {
            remove_artificial_variables();
        }
        // Delete w row
        tableau.erase(tableau.end() - 2);
        return feasibility;
    }

    bool solve_phase_two()
    {
        // Loop until stopping condition: all coefs in z >= 0
        while (!stop_condition(tableau.size()-1))
        {
            // Determine entering variable (most negative)
            int enter = -1;
            double min_coef = -EPS;
            for (int i = 0; i < tableau[0].size()-1; ++i)
            {
                if (tableau.back()[i] < min_coef)
                {
                    min_coef = tableau.back()[i];
                    enter = i;
                }
            }
            // Determine leaving variable (minimum ratio test)
            int out = -1;
            double min_ratio;
            for (int i = 0; i < num_const; ++i)
            {
                if (tableau[i][enter] > EPS)
                {
                    double ratio = tableau[i].back() / tableau[i][enter];
                    if (out == -1 || ratio < min_ratio)
                    {
                        min_ratio = ratio;
                        out = i;
                    }
                }
            }
            // If no leaving variable found, problem is unbounded
            if (out == -1)
                return false;
            // Else, pivot
            else
                pivot(enter, out);
        }
        return true;
    }

public:
    Simplex(const vector<int>& goal_func, const vector<vector<int>>& constraints,
        const vector<int>& const_signs)
    : goal_func(goal_func), constraints(constraints), const_signs(const_signs)
    {
        sol_vars = goal_func.size();
        extra_vars = constraints[0].size() - 1 - sol_vars;
        for (int i = 0; i < extra_vars; ++i)
            this->goal_func.push_back(0);
        num_const = constraints.size();
    }

    void solve()
    {
        // Transform >= constraints into <=
        normalize_constraints();

        // Initialize tableau
        initialize_problem();

        // Solve phase I
        feas = solve_phase_one();

        // Solve phase II
        if (feas)
            unb = !solve_phase_two();

        // Extract solution
        if (feas && !unb)
        {
            solution = vector<double>(sol_vars, 0);
            for (int i = 0; i < base_vars.size(); ++i)
            {
                if (base_vars[i] < solution.size())
                    solution[base_vars[i]] = tableau[i].back();
            }
        }
    }

    vector<double> get_solution() const
    {
        return solution;
    }

    double get_optimal_value() const
    {
        return -tableau.back().back();
    }

    bool is_feasible() const { return feas; }
    bool is_unbounded() const { return unb; }

    vector<vector<int>> get_restrictions() const { return constraints; }
    vector<int> get_restr_signs() const { return const_signs; }

};


int main()
{
    ifstream fin("input.txt");

    int result = 0;
    string lights_str;
    while (fin >> lights_str)
    {
        // Process lights
        int size = lights_str.size() - 2;

        // Process buttons
        vector<vector<int>> buttons;
        string button_str;
        fin >> button_str;
        while (button_str[0] == '(')
        {
            istringstream sin(button_str);
            char aux;
            int num;
            vector<int> button;
            sin >> aux;
            while (sin >> num >> aux)
                button.push_back(num);
            buttons.push_back(button);
            fin >> button_str;
        }

        // Process joltage
        vector<int> joltage;
        istringstream sin(button_str);
        char aux;
        int num;
        while (sin >> aux >> num)
            joltage.push_back(num);

        // Transform into constraints
        vector<vector<int>> constraints = vector<vector<int>>(size, vector<int>(buttons.size()+1, 0));
        for (int i = 0; i < buttons.size(); ++i)
            for (int j = 0; j < buttons[i].size(); ++j)
                constraints[buttons[i][j]][i] = 1;
        for (int i = 0; i < joltage.size(); ++i)
            constraints[i].back() = joltage[i];

        // Goal function
        vector<int> goal_func = vector<int>(buttons.size(), 1);

        Simplex simplex(goal_func, constraints, vector<int>(size, 0));
        queue<Simplex> to_solve;
        to_solve.push(simplex);

        int best = -1;
        while (!to_solve.empty())
        {
            Simplex current = to_solve.front();
            to_solve.pop();
            current.solve();
            if (current.is_feasible() && !current.is_unbounded())
            {
                vector<double> sol = current.get_solution();
                int frac = -1;
                for (int i = 0; i < sol.size(); ++i)
                {
                    if (fabs(sol[i] - round(sol[i])) > EPS)
                    {
                        frac = i;
                        break;
                    }
                }
                // Integer solution found
                if (frac == -1)
                {
                    if (best == -1 || current.get_optimal_value() < best)
                        best = current.get_optimal_value();
                }
                // Branch if relaxed solution is promising
                else if (best == -1 || current.get_optimal_value() < best)
                {
                    // Floor branch
                    vector<vector<int>> new_restrictions = current.get_restrictions();
                    new_restrictions.push_back(vector<int>(new_restrictions[0].size(), 0));
                    new_restrictions.back()[frac] = 1;
                    new_restrictions.back().back() = floor(sol[frac]);
                    vector<int> const_signs = current.get_restr_signs();
                    const_signs.push_back(1);
                    Simplex down = Simplex(goal_func, new_restrictions, const_signs);
                    to_solve.push(down);
                    // Ceil branch
                    new_restrictions.back().back() = ceil(sol[frac]);
                    const_signs.back() = -1;
                    Simplex up = Simplex(goal_func, new_restrictions, const_signs);
                    to_solve.push(up);
                }
            }
        }

        result += best;
    }

    cout << "Result: " << result << '\n';
    return 0;
}