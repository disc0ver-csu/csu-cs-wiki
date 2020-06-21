package experiment5.HelloApp;


/**
* src/experiment5/HelloApp/_HelloImplBase.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从src/experiment5/Hello.idl
* 2020年6月11日 星期四 下午06时06分53秒 CST
*/

public abstract class _HelloImplBase extends org.omg.CORBA.portable.ObjectImpl
                implements experiment5.HelloApp.Hello, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors
  public _HelloImplBase ()
  {
  }

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("asyHello", new java.lang.Integer (0));
  }

  public org.omg.CORBA.portable.OutputStream _invoke (String $method,
                                org.omg.CORBA.portable.InputStream in,
                                org.omg.CORBA.portable.ResponseHandler $rh)
  {
    org.omg.CORBA.portable.OutputStream out = null;
    java.lang.Integer __method = (java.lang.Integer)_methods.get ($method);
    if (__method == null)
      throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);

    switch (__method.intValue ())
    {
       case 0:  // src/experiment5/HelloApp/Hello/asyHello
       {
         String sayHello = in.read_string ();
         String $result = null;
         $result = this.asyHello (sayHello);
         out = $rh.createReply();
         out.write_string ($result);
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:src/experiment5/HelloApp/Hello:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }


} // class _HelloImplBase
