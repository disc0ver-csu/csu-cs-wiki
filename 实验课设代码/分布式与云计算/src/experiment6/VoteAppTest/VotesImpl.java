/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: VotesImpl
 * Author:   ITryagain
 * Date:     2020/6/16 13:43
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package experiment6.VoteAppTest;

import VoteAppTest.Vote;

import java.util.HashMap;
import java.util.Map;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/16
 * @since 1.0.0
 */

public class VotesImpl extends VoteAppTest._VotesImplBase {

    Vote[] votes = null;
    HashMap<String, Integer> hashMap = new HashMap<String, Integer>();

    @Override
    public void castVote(String name) {
        if(hashMap.containsKey(name)){
            int value = hashMap.get(name);
            hashMap.replace(name, value + 1);
        }else{
            hashMap.put(name, 1);
        }
        System.out.println(name + " 获得一票");
    }

    @Override
    public Vote[] getList() {
        this.votes = new Vote[hashMap.size()];
        int i = 0;
        for(Map.Entry<String, Integer> entry: hashMap.entrySet()){
            votes[i++] = new Vote(entry.getKey(), entry.getValue());
            System.out.println(i + " " + entry.getKey() + " 获得 " + entry.getValue() + " 票");
        }
        return votes;
    }

    @Override
    public void getList(Vote[] newGetList) {
//        this.votes = newGetList;
    }
}
