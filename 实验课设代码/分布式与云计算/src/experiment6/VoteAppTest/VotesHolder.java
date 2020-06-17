package VoteAppTest;

/**
* VoteAppTest/VotesHolder.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

public final class VotesHolder implements org.omg.CORBA.portable.Streamable
{
  public VoteAppTest.Votes value = null;

  public VotesHolder ()
  {
  }

  public VotesHolder (VoteAppTest.Votes initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VoteAppTest.VotesHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VoteAppTest.VotesHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VoteAppTest.VotesHelper.type ();
  }

}
