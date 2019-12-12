#include <gtest/gtest.h>
#include "../TextProcesor/Parser.h"
#include "../TextProcesor/Invoker.h"
#include "../TextProcesor/document.h"
#include "../TextProcesor/command.h"
#include <sstream>
//#include "pch.h"

TEST(InsertTest, emptyDoc) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp{ "\"111\" 0" };
	inv.Do("insert", inp);
	EXPECT_EQ(doc.data(), "111");
}

TEST(InsertTest, notEmptyDoc) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp{ "\"111\" 0" };
	inv.Do("insert", inp);
	std::istringstream inp2{ "\"222\" 0" };
	inv.Do("insert", inp2);
	EXPECT_EQ(doc.data(), "222111");
}

TEST(InsertTest, outOfDoc) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp{ "\"111\" 10" };
	inv.Do("insert", inp);
	EXPECT_EQ(doc.data(), "111");
}

TEST(InsertTest, negativeInsertPos) {
	
}

TEST(DeleteTest, emptyDoc) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp{ "1 4" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc.data(), "");
}

TEST(DeleteTest, notEmptyDoc) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 2" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc.data(), "111");
}

TEST(DeleteTest, swapIndexes) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "2 0" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc.data(), "111");
}

TEST(DeleteTest, equalIndexes) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "0 0" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc.data(), "22111");
}

TEST(DeleteTest, outOfDocIndex) {
	Document doc;
	Invoker inv(&doc);
	std::istringstream inp2{ "\"222111\" 0" };
	inv.Do("insert", inp2);
	std::istringstream inp{ "10 20" };
	inv.Do("delete", inp);
	EXPECT_EQ(doc.data(), "222111");
}

TEST(CopyPasteTest, emptyDoc) {

}

TEST(CopyPasteTest, normalTest) {

}

TEST(CopyPasteTest, outOfDocIndexes) {

}

TEST(CopyPasteTest, swapIndexes) {

}

TEST(CopyPasteTest, equalIndexes) {

}
/*
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ParserTest, _insert) {
	cmd a("insert \"123\" 0");
	EXPECT_EQ(a.code, 'i');
	EXPECT_EQ(a.str, "123");
	EXPECT_EQ(a.idx1, 0);
}

TEST(ParserTest, _delete) {
	cmd a("delete 0 5");
	EXPECT_EQ(a.code, 'd');
	EXPECT_EQ(a.idx1, 0);
	EXPECT_EQ(a.idx2, 5);
}

TEST(ParserTest, _copy) {
	cmd a("copy 0 5");
	EXPECT_EQ(a.code, 'c');
	EXPECT_EQ(a.idx1, 0);
	EXPECT_EQ(a.idx2, 5);
}

TEST(ParserTest, _paste) {
	cmd a("paste 0");
	EXPECT_EQ(a.code, 'p');
	EXPECT_EQ(a.idx1, 0);
}

TEST(ParserTest, _undo) {
	cmd a("undo");
	EXPECT_EQ(a.code, 'u');
}

TEST(ParserTest, _redo) {
	cmd a("redo");
	EXPECT_EQ(a.code, 'r');
}

TEST(ParserTest, _unknownCommand) {
	//cmd a;
	//EXPECT_THROW(cmd a("qqq"), UnknownCommandException());
}

TEST(InsertTest, emptyDoc) {
	Document doc;
	Invoker inv(&doc);
	cmd command("insert \"hello\" 0");
	inv.Do(command);
	EXPECT_EQ(doc.data(), "hello");
}

TEST(InsertTest, notEmptyDoc) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"111\" 0");
	inv.Do(command1);
	ASSERT_EQ(doc.data(), "111");
	cmd command2("insert \"222\" 3");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "111222");
}

TEST(InsertTest, negativePosForInsert) {
	Document doc;
	Invoker inv(&doc);
	cmd command("insert \"hello\" -1");
	inv.Do(command);
	EXPECT_EQ(doc.data(), "hello");
}

TEST(InsertTest, outOfDocPosForInsert) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"111\" 0");
	inv.Do(command1);
	ASSERT_EQ(doc.data(), "111");
	cmd command2("insert \"222\" 5");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "111222");
}

TEST(CopyTest, EmptyDocCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command("copy 0 0");
	inv.Do(command);
	EXPECT_EQ(doc.buffer(), "");
}

TEST(PasteTest, EmptyDocCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("copy 0 0");
	inv.Do(command1);
	cmd command2("paste 0");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "");
}

TEST(CopyTest, NormalCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 0 2");
	inv.Do(command2);
	EXPECT_EQ(doc.buffer(), "123");
}

TEST(PasteTest, NormalCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 0 2");
	inv.Do(command2);
	cmd command3("paste 3");
	inv.Do(command3);
	EXPECT_EQ(doc.data(), "123123");
}

TEST(CopyPasteTest, outOfDocIndexCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 3 4");
	inv.Do(command2);
	EXPECT_EQ(doc.buffer(), "");
}

TEST(CopyTest, eqIndexCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 0 0");
	inv.Do(command2);
	EXPECT_EQ(doc.buffer(), "1");
}

TEST(PasteTest, eqIndexCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 0 0");
	inv.Do(command2);
	cmd command3("paste 3");
	inv.Do(command3);
	EXPECT_EQ(doc.data(), "1231");
}

TEST(CopyTest, invertIndexCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 2 0");
	inv.Do(command2);
	EXPECT_EQ(doc.buffer(), "1");
}

TEST(PasteTest, invertIndexCopy) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("copy 2 0");
	inv.Do(command2);
	cmd command3("paste 3");
	inv.Do(command3);
	EXPECT_EQ(doc.data(), "1231");
}

TEST(DeleteTest, emptyDoc) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("delete 0 0");
	inv.Do(command1);
	EXPECT_EQ(doc.data(), "");
}

TEST(DeleteTest, normalDelete) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("delete 0 1");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "3");
}

TEST(DeleteTest, eqIndexDelete) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("delete 2 2");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "12");
}

TEST(DeleteTest, outOfDocIndexDelete) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("delete 3 4");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "123");
}

TEST(DeleteTest, invertedIndexDelete) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	cmd command2("delete 3 1");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "13");
}

TEST(UndoTest, emptyCommandList) {
	Document doc;
	Invoker inv(&doc);
	cmd command2("undo");
	inv.Do(command2);
	EXPECT_EQ(doc.data(), "");
}

TEST(UndoTest, normalUndo) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Undo();
	EXPECT_EQ(doc.data(), "");
}

TEST(RedoTest, emptyCommandList) {
	Document doc;
	Invoker inv(&doc);
	inv.Redo();
	EXPECT_EQ(doc.data(), "");
}

TEST(RedoTest, normalRedo) {
	Document doc;
	Invoker inv(&doc);
	cmd command1("insert \"123\" 0");
	inv.Do(command1);
	inv.Undo();
	inv.Redo();
	EXPECT_EQ(doc.data(), "123");
}*/