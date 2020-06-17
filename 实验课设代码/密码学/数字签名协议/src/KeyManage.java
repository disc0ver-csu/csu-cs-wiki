/**
 * Copyright (C), 2015-2019, XXX有限公司
 * FileName: KeyManage
 * Author:   ITryagain
 * Date:     2019/6/10 19:21
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */

import java.io.*;
import java.math.BigInteger;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
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

public class KeyManage {


    public void saveKey() throws Exception{

        KeyPair keyPair = initKey(2048);
        RSAPrivateKey rsaPrivateKey = (RSAPrivateKey)keyPair.getPrivate();
        RSAPublicKey rsaPublicKey = (RSAPublicKey)keyPair.getPublic();

        savePrivateKey(keyPair);
        savePublicKey(keyPair);
        System.out.println("Private_Key: \t" + new BigInteger(rsaPrivateKey.getModulus().toString(), 10).toString(2));
        System.out.println("Public_Key: \t" + rsaPublicKey.getPublicExponent());
    }

    /**
     *  初始化密钥
     * @param len
     * @return
     */
    public KeyPair initKey(int len){
        try{
            KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
            keyPairGenerator.initialize(len);
            KeyPair keyPair = keyPairGenerator.generateKeyPair();
            return keyPair;
        }catch(NoSuchAlgorithmException e){
            e.printStackTrace();
        }
        return null;
    }

    public static void savePublicKey(KeyPair keyPair) throws Exception{
        RSAPublicKey rsaPublicKey = (RSAPublicKey) keyPair.getPublic();

        byte[] bytes = rsaPublicKey.getEncoded();
//        System.out.println(bytes);
        String pubKeyStr = util.toHexString(bytes);

        BufferedWriter out = new BufferedWriter(new FileWriter("publickey.txt"));
        out.write(pubKeyStr);
        out.close();
    }


    public static void savePrivateKey(KeyPair keyPair) throws Exception{
        RSAPrivateKey rsaPrivateKey = (RSAPrivateKey) keyPair.getPrivate();

        byte[] bytes = rsaPrivateKey.getEncoded();
        String priKeyStr = util.toHexString(bytes);

        BufferedWriter out = new BufferedWriter(new FileWriter("privatekey.txt"));
        out.write(priKeyStr);
        out.close();
    }

    public RSAPublicKey loadPublickey() throws IOException, NoSuchAlgorithmException, InvalidKeySpecException {
        BufferedReader in = new BufferedReader(new FileReader("publickey.txt"));
        // 读取key 转换成数组
        byte[] bytes = util.toByteArray(in.readLine());
//        System.out.println(bytes);
        // 将数组转成publickey
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(bytes);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        RSAPublicKey publicKey = (RSAPublicKey)keyFactory.generatePublic(x509EncodedKeySpec);
        System.out.println(publicKey);
        return publicKey;
    }

    public RSAPrivateKey loadPrivatekey() throws  IOException, NoSuchAlgorithmException, InvalidKeySpecException{
        BufferedReader in = new BufferedReader(new FileReader("privatekey.txt"));
        // 读取key 转换成数组
        byte[] bytes = util.toByteArray(in.readLine());
        // 将数组转成publickey
        PKCS8EncodedKeySpec pkcs8EncodedKeySpec = new PKCS8EncodedKeySpec(bytes);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        RSAPrivateKey privateKey = (RSAPrivateKey)keyFactory.generatePrivate(pkcs8EncodedKeySpec);
        System.out.println(new BigInteger(privateKey.getModulus().toString(), 10).toString(2));
        return privateKey;
    }
}
