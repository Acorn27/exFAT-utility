load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# http archive is prefered to git_repository/new git_repository
http_archive(

    # unique nanme for this repostitory, use for deps field
    name = "gtest",

    # url of zip file
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
    
    # must match with the download file, (but optional)
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    
    # specify the use to use as the BUILD files for this repository
    # name does not have to be BUILD
    # use "@//" for main repo
    build_file = "@//:gtest.BUILD",

    # remove redundant folder created by unzip
    strip_prefix = "googletest-release-1.10.0",
)

