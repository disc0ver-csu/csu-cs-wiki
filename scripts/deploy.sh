###
 # @Description: 
 # @Author: 妄想
 # @Date: 2020-06-19 12:37:24
 # @LastEditTime: 2020-06-19 13:13:04
 # @LastEditors: 妄想
### 
#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=leo6033
REPO=CSU_CS_Experiment
# This probably should match an email for one of your users.
EMAIL=long452a@163.com

set -e

git remote add gh-token "https://${GH_TOKEN}@github.com/$ORG/$REPO.git";
git fetch gh-token && git fetch gh-token gh-pages:gh-pages;

git config user.name "leo6033"
git config user.email "$EMAIL"

mkdocs gh-deploy -v --clean --remote-name gh-token;