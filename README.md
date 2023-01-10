# For Developer and Maintainer

Set project git hooks by command

```bash
git config core.hooksPath .githooks
```

Container

```bash
docker build -t toolbox .

docker run -d --name toolbox --restart always \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v /srv/gitlab-runner/config:/etc/gitlab-runner \
  toolbox
```
