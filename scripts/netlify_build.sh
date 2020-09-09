###
 # @Description: 
 # @Author: 妄想
 # @Date: 2020-06-17 14:17:14
 # @LastEditTime: 2020-06-17 14:22:28
 # @LastEditors: 妄想
### 
#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=CSU
REPO=csu-cs-wiki
# This probably should match an email for one of your users.
EMAIL=csulmw@163.com

set -e

# Clone Theme for Editing
if [ ! -d "mkdocs-material" ] ; then
  git clone --depth=1 https://github.com/leo6033/mkdocs-material.git
fi

git rev-parse --short HEAD | xargs -I % sed -i "s/githash: ''/githash: '%'/g" mkdocs.yml
sed -i "s/name: 'material'/name: null\n  custom_dir: 'mkdocs-material\/material'\n  static_templates:\n    - 404.html/g" mkdocs.yml
# sed -i "s/- 'https:\/\/cdnjs.loli.net\/ajax\/libs\/mathjax\/2.7.5\/MathJax.js?config=TeX-MML-AM_CHTML'//g" mkdocs.yml

mkdocs build -v

# find ./site -type f -name '*.html' -exec node --max_old_space_size=512 ./scripts/render_math.js {} \;

# find ./site -type f -name "*.html" -exec sed -i -E 's/([^"]*)(assets[^"]*)/https:\/\/cdn-for-oi-wiki.billchn.com\/\2/g' {} +

# npx gulp minify
# try to avoid netlify timeout
