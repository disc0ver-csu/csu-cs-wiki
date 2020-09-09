import os
f = open('site/_redirects')
nginx = open('site/redirect-nginx.conf', 'w')
for cur in f.readlines():
    s, t = cur.strip().split(' ')
    # s = s.rstrip('/') + '(\/?(index\.html)?)'
    # t = 'https://leo6033.github.io/csu-cs-wiki/' + t + ';'
    # nginx.write('~' + s + ' ' + t + "\n")
    html_path = os.path.join('site', s.lstrip('/'), 'index.html')
    os.makedirs(os.path.dirname(html_path), exist_ok=True)
    with open(html_path, 'w') as html_file:
        # print(f"<script type=\"text/javascript\">location.href=\"{t}\"</script>")
        html_file.write(f"<script type=\"text/javascript\">location.href=\"{t}\"</script>\n")
        # print(html_path)
