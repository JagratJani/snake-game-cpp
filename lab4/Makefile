# lab4/Makefile
# Builds and runs Part B tests (Rules 1-4) and Part D seam test.
# Usage:
#   make partb        # build Part B test binary
#   make partd        # build Part D seam test binary
#   make run_partb    # build + run Part B
#   make run_partd    # build + run Part D
#   make coverage     # build with --coverage, run, then gcov

GTEST_DIR = googletest-release-1.10.0/googletest
SRC_DIR   = ../src

CXXFLAGS  = -std=gnu++14 -I$(GTEST_DIR)/include -I$(SRC_DIR) -Istubs -DGTEST_HAS_PTHREAD=0 -DGTEST_HAS_POSIX_RE=0 -Wall
GTEST_SRC = $(GTEST_DIR)/src/gtest_main.cc $(GTEST_DIR)/src/gtest-all.cc

# ── Part B ────────────────────────────────────────────────────────────────────
PARTB_SRCS = test_snake_rules.cpp \
             $(SRC_DIR)/Snake.cpp  \
             $(SRC_DIR)/Food.cpp

partb: $(GTEST_SRC) $(PARTB_SRCS)
	g++ $(CXXFLAGS) -I$(GTEST_DIR) $(PARTB_SRCS) $(GTEST_SRC) -o test_partb.exe

run_partb: partb
	./test_partb.exe

# ── Part D ────────────────────────────────────────────────────────────────────
PARTD_SRCS = test_seam_rand.cpp    \
             $(SRC_DIR)/Snake.cpp  \
             $(SRC_DIR)/Food.cpp

partd: $(GTEST_SRC) $(PARTD_SRCS)
	g++ $(CXXFLAGS) -I$(GTEST_DIR) $(PARTD_SRCS) $(GTEST_SRC) -o test_partd.exe

run_partd: partd
	./test_partd.exe

# ── Coverage (Part C) ─────────────────────────────────────────────────────────
coverage:
	g++ $(CXXFLAGS) -I$(GTEST_DIR) --coverage -O0 -g $(PARTB_SRCS) $(GTEST_SRC) -o test_cov.exe
	./test_cov.exe
	gcov -b $(SRC_DIR)/Snake.cpp $(SRC_DIR)/Food.cpp

.PHONY: partb partd run_partb run_partd coverage
