/**
 * Copyright (C), 2015-2019, XXX有限公司
 * FileName: digitsign
 * Author:   ITryagain
 * Date:     2019/6/10 18:12
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */


import java.io.*;
import java.security.*;
import java.security.interfaces.RSAPrivateKey;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;


/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2019/6/10
 * @since 1.0.0
 */

public class DigitSign {

    public static void main(String[] args){
        KeyManage keyManage = new KeyManage();
//        try {
//            keyManage.saveKey();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
        RSAPublicKey rsaPublicKey = null;
        RSAPrivateKey rsaPrivateKey = null;
        try {
            rsaPublicKey = keyManage.loadPublickey();
            rsaPrivateKey = keyManage.loadPrivatekey();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (InvalidKeySpecException e) {
            e.printStackTrace();
        }

        String filename = "a1.jpg";
        String src = getMD5Digest(filename,"SHA-256");
        System.out.println("SHA-256:\t"+src);
        byte[] result = sign(rsaPrivateKey, src);
        System.out.println("RSA 签名： \t" +util.toHexString(result));
        verify(rsaPublicKey, result, src);
        String src_tmp = tamper("123",filename);
        verify(rsaPublicKey, result, src_tmp);
    }

    public static byte[] sign(RSAPrivateKey rsaPrivateKey, String src){
        PKCS8EncodedKeySpec pkcs8EncodedKeySpec = new PKCS8EncodedKeySpec(rsaPrivateKey.getEncoded());
        try{
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            PrivateKey privateKey = keyFactory.generatePrivate(pkcs8EncodedKeySpec);

            Signature signature = Signature.getInstance("SHA256withRSA");
            signature.initSign(privateKey);

            signature.update(src.getBytes());
            byte[] bytes = signature.sign();
            return bytes;
        }catch(Exception e){
            e.printStackTrace();
        }
        return null;
    }

    public static void verify(RSAPublicKey rsaPublicKey, byte[] result, String src){
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(rsaPublicKey.getEncoded());
        try{
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            PublicKey publicKey = keyFactory.generatePublic(x509EncodedKeySpec);
            Signature signature = Signature.getInstance("SHA256withRSA");
            signature.initVerify(publicKey);
            signature.update(src.getBytes());
            boolean bool = signature.verify(result);
            System.out.println("文件是否未被篡改？\t"+bool);

        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public static String getMD5Digest(String fileName, String algorithm){
        try{
            int count;
            byte[] bytes = new byte[8192];
            MessageDigest messageDigest = MessageDigest.getInstance(algorithm);
            BufferedInputStream bis = new BufferedInputStream(new FileInputStream(fileName));
            while((count = bis.read(bytes)) > 0){
                messageDigest.update(bytes, 0, count);
            }
            bis.close();
            return util.toHexString(messageDigest.digest());
        }catch(NoSuchAlgorithmException | IOException e){
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 篡改文件
     */
    public static String tamper(String str, String fileName){
        try{
            BufferedWriter out = new BufferedWriter(new FileWriter(fileName,true));
            out.write(str);
            out.close();
            String src = getMD5Digest(fileName, "SHA-256");
            System.out.println("Tampered SHA-256: \t" + src);
            return src;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }

}
