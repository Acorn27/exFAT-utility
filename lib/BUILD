load("@rules_cc//cc:defs.bzl", "cc_library")

# parse command
cc_library(
    name = "parse-command",
    srcs = ["parse-command.cc"],
    hdrs =  ["include/parse-command.h"],
    copts = ["-Ilib/include"],
    visibility = ["//visibility:public"],
)

#copy image
cc_library(
    name = "copy-image",
    srcs = ["copy-image.cc"],
    hdrs =  ["include/copy-image.h",
            "include/exfat.h",
            "include/file-handler.h"],

    deps = ["//lib:file-handler"],
    copts = ["-Ilib/include"],
    visibility = ["//visibility:public"],
)

# file handler
cc_library(
    name = "file-handler",
    srcs = ["file-handler.cc"],
    hdrs =  ["include/file-handler.h",
            "include/exfat.h",],
    copts = ["-Ilib/include"],
    visibility = ["//visibility:public"],
)

# verify image
cc_library(
    name = "verify-image",
    srcs = ["verify-image.cc"],
    hdrs =  ["include/verify-image.h",
            "include/exfat.h",],
    copts = ["-Ilib/include"],
    deps = ["//lib:file-handler"],
    visibility = ["//visibility:public"],
)