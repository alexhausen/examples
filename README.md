# PoC
Proof of Concept tests

Just a sandbox with code examples and fun stuff (it doesn't always work).

Adapt your existing local / cloned repos to token based auth:
```
git remote remove origin
git remote add origin https://[TOKEN]@github.com/[USER]/[REPO]
git push
```

Clone repos using token based authentication (non public repos):
```
git clone https://<username>:<token>@github.com/<accountname>/<reponame>
```
