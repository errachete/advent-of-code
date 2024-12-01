FROM    ubuntu:latest

# Install dependencies
RUN     apt-get -y update \
&&      apt-get -y --no-install-recommends install \
        ca-certificates \
        gcc \
        gdb \
        git \
        g++ \
&&      rm -rf /var/lib/apt/lists/*

# Add user and group
RUN     groupadd -r appgroup \
&&      useradd -r -g appgroup appuser
USER    appuser
WORKDIR /home/appuser

# Configure useful aliases
RUN     echo "export PS1='\[\e[32m\][\[\e[m\]\[\e[31m\]\u\[\e[m\]\[\e[33m\]@\[\e[m\]\[\e[32m\]\h\[\e[m\]:\[\e[36m\]\w\[\e[m\]\[\e[32m\]]\[\e[m\] '" >> ~/.bashrc \
&&      echo "alias la='ls --color=auto'" >> ~/.bashrc \
&&      echo "alias ll='ls -laF --color=auto'" >> ~/.bashrc \
&&      echo "alias lt='ls -lt --color=auto'" >> ~/.bashrc

# Command to make container to stop after exit vscode
CMD     ["sh", "-c", "while sleep 120 && ps aux | egrep 'vscode.*[b]ootstrap-fork.*extensionHost.*' > /dev/null; do :; done"]