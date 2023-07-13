cc_test(
    name = "parse-unittest",
    srcs = ["parse_unittest.cc"],
    copts = ["-Iexternal/gtest/include",
            "-Ilib/include"
    ],
    deps = [
        "@googletest//:gtest_main",
        "//lib:parse-command",
    ],
)