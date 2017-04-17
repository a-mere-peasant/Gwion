#!/bin/bash

# TODO: output error message
check_variable() {
	if [ -z "$1" ]
	then
		echo "unknown variable $2."
		exit 1
	fi
}

check_variable "$TRAVIS_OS_NAME" TRAVIS_OS_NAME
check_variable "$GWION_DOC_DIR" GWION_DOC_DIR
check_variable "$GWION_API_DIR" GWION_API_DIR
check_variable "$GWION_TOK_DIR" GWION_TOK_DIR
check_variable "$GWION_TAG_DIR" GWION_TAG_DIR
check_variable "$GWION_ADD_DIR" GWION_PLUG_DIR

brew_dependencies() {
	brew install libsndfile # needed for soundpipe
	brew install valgrind   # needed for test
}

build_soundpipe() {
	[ "$USE_DOUBLE" -eq 0 ] && export SPFLOAT="float"
	[ -z "$USE_DOUBLE" ] && export SPFLOAT="float"
	[ "$USE_DOUBLE" -eq 0 ] && unset USE_DOUBLE
	make
}

check_soundpipe() {
	[ -d Soundpipe ] || {
	    if [ "$SP_BRANCH"" ]
			git clone -b "$SP_BRANCH" https://github.com/paulbatchelor/Soundpipe.git
		else
			git clone -b https://github.com/paulbatchelor/Soundpipe.git
		fi
		pushd Soundpipe
		build_soundpipe
		popd
		return 0
	}
	pushd Soundpipe
	git fetch
	[ "$(git rev-parse HEAD)" = "$(git rev-parse @{u})" ] || build_soundpipe
	popd
	return 0
}

prepare_directories() {
	mkdir -p doc/{dat,dot,map,png,rst,search,tex}
	mkdir -p api
	mkdir -p tag
	mkdir -p tok
	mkdir -p add
}

[ "$TRAVIS_OS_NAME" = "osx" ] && brew_dependencies

check_soundpipe
prepare_directories
exit 0
