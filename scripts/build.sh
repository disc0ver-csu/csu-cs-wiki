#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=disc0ver-csu
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
#Will NOT Use Mathjax for Deploy
set -i "s/- 'https:\/\/cdn.jsdelivr.net\/npm\/mathjax@2.7.5\/MathJax.js?config=TeX-MML-AM_CHTML'//g" mkdocs.yml
# sed -i "s/- 'https:\/\/cdnjs.loli.net\/ajax\/libs\/mathjax\/2.7.5\/MathJax.js?config=TeX-MML-AM_CHTML'//g" mkdocs.yml