FROM gitlab/gitlab-runner:latest
ENV PATH="/root/miniconda3/bin:${PATH}"
ARG PATH="/root/miniconda3/bin:${PATH}"
RUN apt update
RUN apt install xz-utils -y

RUN wget https://github.com/mvdan/sh/releases/download/v3.6.0/shfmt_v3.6.0_linux_amd64
RUN cp shfmt_v3.6.0_linux_amd64 /usr/local/bin/shfmt
RUN chmod +x /usr/local/bin/shfmt

RUN wget -qO- https://github.com/koalaman/shellcheck/releases/download/v0.9.0/shellcheck-v0.9.0.linux.x86_64.tar.xz | tar -xJf -
RUN cp shellcheck-v0.9.0/shellcheck /usr/local/bin/shellcheck
RUN chmod +x /usr/local/bin/shellcheck

RUN wget \
    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && mkdir /root/.conda \
    && bash Miniconda3-latest-Linux-x86_64.sh -b
RUN conda --version
RUN pip install autopep8
RUN pip install pytest
RUN pip install pylint
RUN /bin/bash