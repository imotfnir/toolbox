FROM gitlab/gitlab-runner:latest
ENV PATH="/root/miniconda3/bin:${PATH}"
ARG PATH="/root/miniconda3/bin:${PATH}"
RUN apt update

RUN cd /root
RUN wget https://github.com/mvdan/sh/releases/download/v3.6.0/shfmt_v3.6.0_linux_amd64 && cp shfmt_v3.6.0_linux_amd64 /usr/local/bin/shfmt

RUN apt install xz-utils -y
RUN wget -qO- https://github.com/koalaman/shellcheck/releases/download/v0.9.0/shellcheck-v0.9.0.linux.x86_64.tar.xz | tar -xJf -
RUN cd shellcheck-v0.9.0/ \
    sudo cp shellcheck /usr/local/bin

RUN cd /root
RUN wget \
    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && mkdir /root/.conda \
    && bash Miniconda3-latest-Linux-x86_64.sh -b
RUN conda --version
RUN pip install autopep8
RUN /bin/bash