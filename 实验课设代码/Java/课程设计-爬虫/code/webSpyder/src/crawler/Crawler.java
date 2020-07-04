package crawler;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.regex.Pattern;

public class Crawler extends Thread {
    private ArrayList<String> urls;
    private boolean saveAsFile;
    public ArrayList<String> result;

    public Crawler(ArrayList<String> urls, boolean saveAsFile){
        this.urls = urls;
        this.saveAsFile = saveAsFile;
    }

    public ArrayList<String> crawl(){
        ArrayList<String> content = new ArrayList<>();
        try {
            for (int i=0; i<urls.size(); i++) {
                System.out.print("Crawling "+urls.get(i)+"...");
                URL url = new URL(urls.get(i));
                HttpURLConnection urlConn = (HttpURLConnection) url.openConnection();
                urlConn.setDoInput(true);
                urlConn.setRequestMethod("GET");
                urlConn.setRequestProperty("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36");

                InputStream input = urlConn.getInputStream();
                InputStreamReader reader = new InputStreamReader(input, "utf-8");
                BufferedReader br = new BufferedReader(reader);

                String tmp = br.readLine();
                String getline=tmp;
                while(getline!=null)  {
                    getline=br.readLine();
                    if(getline!=null) tmp+=getline;
                }
                content.add(tmp);

                System.out.println("\tdone");
            }
        }catch (Exception e){e.printStackTrace();}

        if(saveAsFile){
            try {
                File f = new File("content.txt");
                f.createNewFile();
                BufferedWriter bw = new BufferedWriter(new FileWriter(f));
                String text = "";
                for(int i=0; i<content.size(); i++){
                    text += parseContent(content.get(i)) + "\n\n";
                }
                bw.write(text);
                bw.close();
            }catch (Exception e){e.printStackTrace();}
        }
        return content;
    }

    public String parseContent(String content){
        String res = "";
        java.util.regex.Pattern script;
        java.util.regex.Pattern style;
        java.util.regex.Pattern html_label;
        java.util.regex.Pattern html_symbol;
        try {
            String script_pattern = "<[\\s]*?script[^>]*?>[\\s\\S]*?<.*?\\/[\\s]*?script[\\s]*?>";
            String style_pattern = "<[\\s]*?style[^>]*?>[\\s\\S]*?<[\\s]*?\\/[\\s]*?style[\\s]*?>";
            String html_label_pattern = "<[^>]+>";
            String html_symbol_pattern = "&.*?;";

            script = Pattern.compile(script_pattern, Pattern.CASE_INSENSITIVE);
            content = script.matcher(content).replaceAll("");

            style = Pattern.compile(style_pattern, Pattern.CASE_INSENSITIVE);
            content = style.matcher(content).replaceAll("");

            html_label = Pattern.compile(html_label_pattern, Pattern.CASE_INSENSITIVE);
            content = html_label.matcher(content).replaceAll(" ");

            html_symbol = Pattern.compile(html_symbol_pattern, Pattern.CASE_INSENSITIVE);
            content = html_symbol.matcher(content).replaceAll("");

            res = content;
        } catch (Exception e) {e.printStackTrace();}

        res = res.replaceAll("[ ]+", " ");
        res = res.replaceAll("[\\t]+", " ");
        res = res.replaceAll("(?m)^\\s*$(\\n|\\r\\n)", "");
        return res;
    }

    @Override
    public void run(){
        result = crawl();
    }
}
