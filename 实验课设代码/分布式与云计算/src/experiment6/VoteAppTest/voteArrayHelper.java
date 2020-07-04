package VoteAppTest;


/**
* VoteAppTest/voteArrayHelper.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

abstract public class voteArrayHelper
{
  private static String  _id = "IDL:VoteAppTest/voteArray:1.0";

  public static void insert (org.omg.CORBA.Any a, VoteAppTest.Vote[] that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static VoteAppTest.Vote[] extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = VoteAppTest.VoteHelper.type ();
      __typeCode = org.omg.CORBA.ORB.init ().create_sequence_tc (0, __typeCode);
      __typeCode = org.omg.CORBA.ORB.init ().create_alias_tc (VoteAppTest.voteArrayHelper.id (), "voteArray", __typeCode);
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static VoteAppTest.Vote[] read (org.omg.CORBA.portable.InputStream istream)
  {
    VoteAppTest.Vote value[] = null;
    int _len0 = istream.read_long ();
    value = new VoteAppTest.Vote[_len0];
    for (int _o1 = 0;_o1 < value.length; ++_o1)
      value[_o1] = VoteAppTest.VoteHelper.read (istream);
    return value;
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, VoteAppTest.Vote[] value)
  {
    ostream.write_long (value.length);
    for (int _i0 = 0;_i0 < value.length; ++_i0)
      VoteAppTest.VoteHelper.write (ostream, value[_i0]);
  }

}
