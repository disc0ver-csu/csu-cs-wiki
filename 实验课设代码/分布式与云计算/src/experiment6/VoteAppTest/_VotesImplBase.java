package VoteAppTest;


/**
* VoteAppTest/_VotesImplBase.java .
* 由IDL-to-Java 编译器 (可移植), 版本 "3.2"生成
* 从Vote.idl
* 2020年6月16日 星期二 下午01时38分26秒 CST
*/

public abstract class _VotesImplBase extends org.omg.CORBA.portable.ObjectImpl
                implements VoteAppTest.Votes, org.omg.CORBA.portable.InvokeHandler
{

  // Constructors
  public _VotesImplBase ()
  {
  }

  private static java.util.Hashtable _methods = new java.util.Hashtable ();
  static
  {
    _methods.put ("castVote", new java.lang.Integer (0));
    _methods.put ("_get_getList", new java.lang.Integer (1));
    _methods.put ("_set_getList", new java.lang.Integer (2));
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
       case 0:  // VoteAppTest/Votes/castVote
       {
         String name = in.read_string ();
         this.castVote (name);
         out = $rh.createReply();
         break;
       }

       case 1:  // VoteAppTest/Votes/_get_getList
       {
         VoteAppTest.Vote $result[] = null;
         $result = this.getList ();
         out = $rh.createReply();
         VoteAppTest.voteArrayHelper.write (out, $result);
         break;
       }

       case 2:  // VoteAppTest/Votes/_set_getList
       {
         VoteAppTest.Vote newGetList[] = VoteAppTest.voteArrayHelper.read (in);
         this.getList (newGetList);
         out = $rh.createReply();
         break;
       }

       default:
         throw new org.omg.CORBA.BAD_OPERATION (0, org.omg.CORBA.CompletionStatus.COMPLETED_MAYBE);
    }

    return out;
  } // _invoke

  // Type-specific CORBA::Object operations
  private static String[] __ids = {
    "IDL:VoteAppTest/Votes:1.0"};

  public String[] _ids ()
  {
    return (String[])__ids.clone ();
  }


} // class _VotesImplBase
