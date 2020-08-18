package VoteAppTest;


/**
* VoteAppTest/voteArrayHolder.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

public final class voteArrayHolder implements org.omg.CORBA.portable.Streamable
{
  public VoteAppTest.Vote value[] = null;

  public voteArrayHolder ()
  {
  }

  public voteArrayHolder (VoteAppTest.Vote[] initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = VoteAppTest.voteArrayHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    VoteAppTest.voteArrayHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return VoteAppTest.voteArrayHelper.type ();
  }

}
