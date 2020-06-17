package VoteAppTest;


/**
* VoteAppTest/VotesOperations.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

public interface VotesOperations 
{
  void castVote (String name);
  VoteAppTest.Vote[] getList ();
  void getList (VoteAppTest.Vote[] newGetList);
} // interface VotesOperations
