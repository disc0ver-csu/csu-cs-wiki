###
 # @Description: 
 # @Author: 妄想
 # @Date: 2020-06-19 12:37:24
 # @LastEditTime: 2020-06-19 12:39:30
 # @LastEditors: 妄想
### 
#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=leo6033
REPO=CSU_CS_Experiment
# This probably should match an email for one of your users.
EMAIL=csulmw@163.com

set -e

git remote add gh-token "https://${GH_TOKEN}@github.com/$ORG/$REPO.git";
git fetch gh-token && git fetch gh-token gh-pages:gh-pages;

# Update git configuration so I can push.
if [ "$1" != "dry" ]; then
    # Update git config.
    git config user.name "csu-cs-wiki"
    git config user.email "$EMAIL"
fi

mkdocs gh-deploy -v --clean --remote-name gh-token;