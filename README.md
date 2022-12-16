# For Developer and Maintainer

Clone this project by command

```bash
git clone http://git162.ufispace.com/bios/bios_test_script/ssdstress.git
```

Set project git hooks by command

```bash
git config core.hooksPath .githooks
```

Container

```bash
docker build -t toolbox .

docker run -d --name gitlab-runner --restart always \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v /srv/gitlab-runner/config:/etc/gitlab-runner \
  toolbox
```
