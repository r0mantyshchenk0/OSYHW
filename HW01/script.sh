#!/usr/bin/env bash

set -euo pipefail

print_help() {
    echo >&2 "Pouziti skriptu:"
    echo >&2 "$(basename "$0") -h | -a | -b | -c | -d <prefix>"
    exit 1
}

while getopts ":habcd:" opt; do
    case "$opt" in
        h|:|\?)
            print_help
            ;;
        a)
            find . -maxdepth 1 -type f \( -iname '*.jpg' -o -iname '*.png' \) -printf '%f\n' | sort
            ;;
        b)
            sed -nE 's/^([[:alpha:]])[+-]?[0-9]+\1[[:blank:]]*//p'
            ;;
        c)
            tr -d '\n' | grep -oE '\+420 ?[0-9]{3} ?[0-9]{3} ?[0-9]{3}' || true
            ;;
        d)
            prefix=$(printf '%s' "$OPTARG" | sed 's/&/\\\&/g')
            sed "s|(file:\([^)]\+\))|(file:${prefix}\1)|g"
            ;;
    esac
    exit 0
done

print_help
