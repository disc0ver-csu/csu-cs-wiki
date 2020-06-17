package VoteAppTest;


/**
* VoteAppTest/Vote.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

public final class Vote implements org.omg.CORBA.portable.IDLEntity
{
  public String name = null;
  public int value = (int)0;

  public Vote ()
  {
  } // ctor

  public Vote (String _name, int _value)
  {
    name = _name;
    value = _value;
  } // ctor

} // class Vote
