package experiment5.HelloApp;


/**
* src/experiment5/HelloApp/HelloHelper.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从src/experiment5/Hello.idl
* 2020年6月11日 星期四 下午06时06分53秒 CST
*/

abstract public class HelloHelper
{
  private static String  _id = "IDL:src/experiment5/HelloApp/Hello:1.0";

  public static void insert (org.omg.CORBA.Any a, experiment5.HelloApp.Hello that)
  {
    org.omg.CORBA.portable.OutputStream out = a.create_output_stream ();
    a.type (type ());
    write (out, that);
    a.read_value (out.create_input_stream (), type ());
  }

  public static experiment5.HelloApp.Hello extract (org.omg.CORBA.Any a)
  {
    return read (a.create_input_stream ());
  }

  private static org.omg.CORBA.TypeCode __typeCode = null;
  synchronized public static org.omg.CORBA.TypeCode type ()
  {
    if (__typeCode == null)
    {
      __typeCode = org.omg.CORBA.ORB.init ().create_interface_tc (experiment5.HelloApp.HelloHelper.id (), "Hello");
    }
    return __typeCode;
  }

  public static String id ()
  {
    return _id;
  }

  public static experiment5.HelloApp.Hello read (org.omg.CORBA.portable.InputStream istream)
  {
    return narrow (istream.read_Object (_HelloStub.class));
  }

  public static void write (org.omg.CORBA.portable.OutputStream ostream, experiment5.HelloApp.Hello value)
  {
    ostream.write_Object ((org.omg.CORBA.Object) value);
  }

  public static experiment5.HelloApp.Hello narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof experiment5.HelloApp.Hello)
      return (experiment5.HelloApp.Hello)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      experiment5.HelloApp._HelloStub stub = new experiment5.HelloApp._HelloStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

  public static experiment5.HelloApp.Hello unchecked_narrow (org.omg.CORBA.Object obj)
  {
    if (obj == null)
      return null;
    else if (obj instanceof experiment5.HelloApp.Hello)
      return (experiment5.HelloApp.Hello)obj;
    else
    {
      org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate ();
      experiment5.HelloApp._HelloStub stub = new experiment5.HelloApp._HelloStub ();
      stub._set_delegate(delegate);
      return stub;
    }
  }

}
