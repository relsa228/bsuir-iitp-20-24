#!/bin/bash

if [ -z $1 ]; then
    git log --graph --abbrev-commit --decorate --date=relative --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --all
else
    if [ -z `cd $1` ]; then
        cd $1
        git log --graph --abbrev-commit --decorate --date=relative --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --all
    fi
    mkdir gitcommitcheck
    cd gitcommitcheck
    git clone $1
    if [ `ls -a | wc -l` -eq 2 ]; then
        cd ..
        sudo rm -r gitcommitcheck
    else
        cd `ls`
        git log --graph --abbrev-commit --decorate --date=relative --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --all
        cd ../..
        sudo rm -r gitcommitcheck
    fi
fi
