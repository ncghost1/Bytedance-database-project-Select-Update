#!/bin/bash

if [ $# != 1 ]
then
  printf '# Error! Please check your usage!\n\n'
  printf '# Usage:\n\tsh fix_format.sh [cpp_code_dir]\n\n'
  printf '# Currently it only supports a directory as the input arg.\n'
  printf '# It scans all the files recursively.\n\n'
  exit 1
fi

# for each .cc & .h files in the given path, fix the format
fix_cc_files () {
  for pathname in "$1"/*; do
	  if [ -d "$pathname" ]; then
      fix_cc_files "$pathname"
	  else
		  case "$pathname" in *.cc | *.h)
			  printf '# fixing %s\n' "$pathname"
        python formatfix.py "$pathname"
		  esac
	  fi
  done
}

CODE_FILE_DIR=$1
CODE_FILE_DIR=${CODE_FILE_DIR%*/}
fix_cc_files ${CODE_FILE_DIR}
