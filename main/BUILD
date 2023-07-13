load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "exfat",
    srcs = ["main.cc"],
    copts = ["-Ilib/include"],
    deps = [
        "//lib:parse-command",
    ],
)