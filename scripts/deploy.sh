###
 # @Description: 
 # @Author: 妄想
 # @Date: 2020-06-19 12:37:24
 # @LastEditTime: 2020-06-19 13:49:24
 # @LastEditors: 妄想
### 
#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=disc0ver-csu
REPO=csu-cs-wiki
# This probably should match an email for one of your users.
EMAIL=long452a@163.com

set -e

git remote add gh-token "https://${GH_TOKEN}@github.com/${GITHUB_NAME}/$REPO.git";
git fetch gh-token && git fetch gh-token gh-pages:gh-pages;

echo $GH_TOKEN
echo $GITHUB_EMAIL
echo $GITHUB_NAME

if [ "$1" != "dry" ]; then
    # Update git config.
    git config user.name "${GITHUB_NAME}"
    git config user.email "${GITHUB_EMAIL}"
fi

mkdocs gh-deploy -v --clean --remote-name gh-token;