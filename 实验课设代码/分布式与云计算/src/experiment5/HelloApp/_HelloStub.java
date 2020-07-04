package experiment5.HelloApp;


/**
* src/experiment5/HelloApp/_HelloStub.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从src/experiment5/Hello.idl
* 2020年6月11日 星期四 下午06时06分53秒 CST
*/

public class _HelloStub extends org.omg.CORBA.portable.ObjectImpl implements experiment5.HelloApp.Hello
{

  public String asyHello (String sayHello)
  {
            org.omg.CORBA.portable.InputStream $in = null;
            try {
                org.omg.CORBA.portable.OutputStream $out = _request ("asyHello", true);
                $out.write_string (sayHello);
                $in = _invoke ($out);
                String $result = $in.read_string ();
                return $result;
            } catch (org.omg.CORBA.portable.ApplicationException $ex) {
                $in = $ex.getInputStream ();
                String _id = $ex.getId ();
                throw new org.omg.CORBA.MARSHAL (_id);
            } catch (org.omg.CORBA.portable.RemarshalException $rm) {
                return asyHello (sayHello        );
            } finally {
                _releaseReply ($in);
            }
  } // asyHello

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:src/experiment5/HelloApp/Hello:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }

  private void readObject (java.io.ObjectInputStream s) throws java.io.IOException
  {
     String str = s.readUTF ();
     String[] args = null;
     java.util.Properties props = null;
     org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, props);
   try {
     org.omg.CORBA.Object obj = orb.string_to_object (str);
     org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl) obj)._get_delegate ();
     _set_delegate (delegate);
   } finally {
     orb.destroy() ;
   }
  }

  private void writeObject (java.io.ObjectOutputStream s) throws java.io.IOException
  {
     String[] args = null;
     java.util.Properties props = null;
     org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init (args, props);
   try {
     String str = orb.object_to_string (this);
     s.writeUTF (str);
   } finally {
     orb.destroy() ;
   }
  }
} // class _HelloStub
