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

# file handling
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

# copy image
cc_test(
    name = "copy-unittest",
    srcs = ["copy-unittest.cc"],
    copts = ["-Iexternal/gtest/include",
            "-Ilib/include"
    ],
    deps = [
        "@googletest//:gtest_main",
        "//lib:copy-image",
    ]
)

# verify image
cc_test(
    name = "verify-unittest",
    srcs = ["verify-unittest.cc"],
    copts = ["-Iexternal/gtest/include",
            "-Ilib/include"
    ],
    deps = [
        "@googletest//:gtest_main",
        "//lib:verify-image",
    ]
)