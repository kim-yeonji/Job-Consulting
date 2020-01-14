# 취업 컨설팅 프로그램

**데이터베이스 (2019년 1학기)**  
설계 프로젝트


## 프로그램 설치 매뉴얼

1. MySQL 데이터베이스를 생성한다.

1. 다음 테이블을 생성한다.

* 사용자 계정
    ``` SQL
    CREATE TABLE user_account (
        account_id      VARCHAR(64) NOT NULL,
        account_pw      VARCHAR(64) NOT NULL,
        account_name    VARCHAR(32) NOT NULL,
        email           VARCHAR(64) NOT NULL,
        PRIMARY KEY (account_id),
        UNIQUE (email)
    );
    ```
    
* 기업 정보
    ``` SQL
    CREATE TABLE company (
        company_id      INT         NOT NULL AUTO_INCREMENT,
        company_name    VARCHAR(32) NOT NULL,
        category        VARCHAR(32) NOT NULL,
        class           VARCHAR(32),
        company_address VARCHAR(128),
        init_salary     INT,
        PRIMARY KEY (company_id)
    );
    ```

* 스펙 정보
    ``` SQL
    CREATE TABLE user_spec (
        account_id      VARCHAR(64) NOT NULL,
        university      VARCHAR(64) NOT NULL,
        major           VARCHAR(64) NOT NULL,
        gpa             FLOAT       NOT NULL,
        toeic           INT,
        opic            INT,
        toeic_speaking  INT,
        cert_count      INT         NOT NULL,
        lang_study      INT         NOT NULL,
        intern          INT         NOT NULL,
        PRIMARY KEY (account_id),
        FOREIGN KEY (account_id) REFERENCES user_account(account_id) ON DELETE CASCADE
    );
    ```

* 합격자 스펙 정보
    ``` SQL
    CREATE TABLE pass_spec (
        spec_no         INT         NOT NULL AUTO_INCREMENT,
        company_id      INT         NOT NULL,
        company_job     VARCHAR(32) NOT NULL,
        university      VARCHAR(64) NOT NULL,
        major           VARCHAR(64) NOT NULL,
        gpa             FLOAT       NOT NULL,
        toeic           INT,
        opic            INT,
        toeic_speaking  INT,
        cert_count      INT         NOT NULL,
        lang_study      INT         NOT NULL,
        intern          INT         NOT NULL,
        PRIMARY KEY (spec_no),
        FOREIGN KEY (company_id) REFERENCES company(company_id) ON DELETE CASCADE
    );
    ```

* 지원자 목록
    ``` SQL
    CREATE TABLE apply_list (
        account_id      VARCHAR(64) NOT NULL,
        company_id      INT         NOT NULL,
        apply_date      DATE        NOT NULL,
        PRIMARY KEY (account_id, company_id),
        FOREIGN KEY (account_id) REFERENCES user_account(account_id) ON DELETE CASCADE,
        FOREIGN KEY (company_id) REFERENCES company(company_id) ON DELETE CASCADE
    );
    ```

1. 아래 sql 파일을 수행해 기업 정보와 합격자 스펙 정보를 테이블에 입력한다.
    * 기업 정보 : [insertData_company.sql](/data/insertData_company.sql)
    * 합격자 스펙 정보 : [insertData_pass_spec.sql](/data/insertData_pass_spec.sql)

1. 설치한 DB의 정보를 이용하여 ODBC 설정 후 코드 상의 DB 정보를 수정한다.


## 프로그램 사용 매뉴얼

1. 첫 화면에서 사용자 계정을 통해 로그인하거나 계정이 없다면 계정을 생성한다.

1. **[나의 스펙 관리]** 메뉴를 통해 자신의 스펙 정보를 입력한다.

1. **[모의 지원]** 메뉴를 통해 원하는 기업에 모의 지원하여 합격자 스펙과 다른 지원자 스펙을 확인하고 자신의 스펙과 비교해볼 수 있다.

1. **[추천 기업 찾기]** 메뉴를 통해 입력한 스펙을 토대로 가장 적합한 기업을 추천받을 수 있다.

1. **[기업 정보]** 메뉴를 통해 등록된 기업의 정보들을 열람할 수 있다.

1. **[개인정보 변경]** 메뉴를 통해 계정 정보를 변경할 수 있다.
