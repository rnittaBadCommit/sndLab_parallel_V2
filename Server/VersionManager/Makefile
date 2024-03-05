# プロジェクトの設定
CXX = g++
CXXFLAGS = -Wall
LDFLAGS = 
SRC_DIRS = . ../Utils
OBJ_DIR = obj
BIN_DIR = bin

# ソースファイルとオブジェクトファイル
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = a.out

# vpathとパターンルールを使用してオブジェクトファイルの依存関係を指定
vpath %.cpp $(SRC_DIRS)

# デフォルトターゲット
all: $(EXECUTABLE)

# 実行ファイルの生成
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# オブジェクトファイルの生成
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# cleanターゲット: オブジェクトファイルと実行ファイルを削除
clean:
	rm -f $(OBJECTS)
	rm -rf $(OBJ_DIR)
	rm -f $(EXECUTABLE)

# .PHONYターゲット: 実際のファイルではなく、コマンドとしてのターゲットを指定
.PHONY: all clean
