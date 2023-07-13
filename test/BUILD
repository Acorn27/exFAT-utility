#parse command
cc_test(
    name = "parse-unittest",
    srcs = ["parse-unittest.cc"],
    copts = ["-Iexternal/gtest/include",
            "-Ilib/include"
    ],
    deps = [
        "@googletest//:gtest_main",
        "//lib:parse-command",
    ],
)

cc_test(
    name = "file-handler-unittest",
    srcs = ["file-handler-unittest.cc"],
    copts = ["-Iexternal/gtest/include",
            "-Ilib/include"
    ],
    deps = [
        "@googletest//:gtest_main",
        "//lib:file-handler",
    ]
)