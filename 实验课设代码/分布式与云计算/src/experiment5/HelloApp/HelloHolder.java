package experiment5.HelloApp;

/**
* src/experiment5/HelloApp/HelloHolder.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从src/experiment5/Hello.idl
* 2020年6月11日 星期四 下午06时06分53秒 CST
*/

public final class HelloHolder implements org.omg.CORBA.portable.Streamable
{
  public experiment5.HelloApp.Hello value = null;

  public HelloHolder ()
  {
  }

  public HelloHolder (experiment5.HelloApp.Hello initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = experiment5.HelloApp.HelloHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    experiment5.HelloApp.HelloHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return experiment5.HelloApp.HelloHelper.type ();
  }

}
