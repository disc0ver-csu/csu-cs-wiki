package VoteAppTest;


/**
* VoteAppTest/VotesHelper.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

abstract public class VotesHelper
{
  private static String  _id = "IDL:VoteAppTest/Votes:1.0";

  public static void insert (org.omg.CORBA.Any a, VoteAppTest.Votes that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static VoteAppTest.Votes extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_interface_tc (VoteAppTest.VotesHelper.id (), "Votes");
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static VoteAppTest.Votes read (org.omg.CORBA.portable.InputStream istream)
  {
    return narrow (istream.read_Object (VoteAppTest._VotesStub.class));
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, VoteAppTest.Votes value)
  {
    ostream.write_Object ((org.omg.CORBA.Object) value);
  }

  public static VoteAppTest.Votes narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VoteAppTest.Votes)
      return (VoteAppTest.Votes)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VoteAppTest._VotesStub stub = new VoteAppTest._VotesStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

  public static VoteAppTest.Votes unchecked_narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof VoteAppTest.Votes)
      return (VoteAppTest.Votes)obj;
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      VoteAppTest._VotesStub stub = new VoteAppTest._VotesStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

}
