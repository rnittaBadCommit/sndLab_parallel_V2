# プロジェクトの設定
CXX = g++
CXXFLAGS =
LDFLAGS =
SRC_DIRS = srcs
OBJ_DIR = obj
BIN_DIR = bin

# ソースファイルを再帰的に検索
SOURCES_ALL = $(shell find $(SRC_DIRS) -name '*.cpp')

# メイン関数のソースファイル
SOURCES_MAIN = $(wildcard $(SRC_DIRS)/test_main/*.cpp)

# クラスなどのソースファイル
SOURCES_CLASS = $(filter-out $(SOURCES_MAIN),$(SOURCES_ALL))

# オブジェクトファイルのパスを生成
OBJECTS_CLASS = $(SOURCES_CLASS:$(SRC_DIRS)/%.cpp=$(OBJ_DIR)/%.o)
OBJECTS_MAIN = $(SOURCES_MAIN:$(SRC_DIRS)/%.cpp=$(OBJ_DIR)/%.o)

# テストの実行ファイル
EXECUTABLE_A = $(BIN_DIR)/test_VersionManager

# デフォルトターゲット
all: $(EXECUTABLE_A)

# 実行ファイルの生成
$(EXECUTABLE_A): $(OBJECTS_CLASS) $(OBJECTS_MAIN)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $^

# オブジェクトファイルの生成
$(OBJ_DIR)/%.o: $(SRC_DIRS)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# cleanターゲット
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# .PHONYターゲット
.PHONY: all clean
