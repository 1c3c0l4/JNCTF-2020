# JNCTF-2020

# 江南大学2020届校赛

- 各位具备`Develop`权限，不能直接Push代码至`Master`，需要建立属于自己的分支，以`Merge Request(Pull Request)`的形式向`Master`提交

- 文件夹结构

```
challenges----|--Pwn--------|---source          # 文件夹。用于放置题目源代码
              |             |---deploy          # 文件夹。部署文件，或题目文件。Pwn和web等在线交			  |				|					  互环境，需提供Dockerfile
              |             |---attachments     # 文件夹。用于向参赛选手，提供赛题相关文件。
              |             |---Write-up.md     # 如题目名所示。            
              |--Web（Web安全）
              |--Reverse（逆向分析）
              |--Misc（杂项）
              |--Crypto（密码学）
              |--Pwn（攻破系统）
              |--data.yml
```

- data.yml 格式

  ```
  JNCTF-2020:
    _meta_:
      - max_score: 500
      - name: "JNCTF-2020"
    Pwn:
      - easy_stack:
        - score: 100
        - flag:
          - random
        - pushflag: ./Pwn/easy_stack/deploy/pushflag.sh
        - env: ./Pwn/easy_stack/deploy/docker-compose.yml
        - attachment:
          - ./Pwn/easy_stack/attachments/easy_stack.tar.gz
        - writeup-cn:
          - ./Pwn/easy_stack/Write-up.md
        - writeup-en: NULL
        - description-cn: NULL
        - description-en: NULL
        - origin: NULL
        - tag: NULL
        - hint: NULL
  ```

  - 其中flag，attachment，writeup，tag，hint都是列表格式。
  - 
  - docker-compose.yml里,version需要等于3
  - origin若无明确指明出题人，填写NULL。
  - tag填写漏洞类型，若不清楚则写NULL，不一定按照出题人的tag。
  - 有docker环境的题目flag必须全为动态，flag字段填写random，pushflag: xxx/xxx.sh，脚本参照大群出题样例，动态flag格式为flag{zheshiflag},静态flag格式为JNCTF{XXXXXXX}
  - 题目如无说明分值,参考其余题目自己设置。
  - docker-compose.yml若没提供，需要自己填写。
  - 题目docker-compose.yml的image字段格式为 `image: 172.18.153.191:5000/xxx_name`。

- Writeup.md 格式

  ```
  # JNCTF-2020 : challenge_name
  ## **【原理】**
  ## **【目的】**
  ## **【环境】**
  ## **【工具】**
  ## **【步骤】**
  ## **【总结】**
  ```