# url 40개 생성하기

ott <- "https://search.naver.com/search.naver?where=news&sm=tab_pge&query=ott&sort=0&photo=0&field=0&pd=3&ds=2019.01.30&de=2021.11.30&cluster_rank=26&mynews=0&office_type=0&office_section_code=0&news_office_checked=&nso=so:r,p:from20190130to20211130,a:all&start="
urls <- NULL
for ( x in 0 : 39){
  urls <- c(urls, paste(ott,x*10+1,sep=''))
}

#HTML추출을 위한 패키지 설치

#install.packages("tidyverse")
#install.packages("rvest")
library(tidyverse)
library(rvest)

# r에 HTML불러오기
news_links <- NULL
for (url in urls){
  html <- read_html(url)
  news_links <- c(news_links, html %>%
                  html_nodes('div > div > div.news_info > div.info_group > a:nth-child(3)') %>%
                  html_attr('href'))
}

# 본문추출
contents <- NULL

for (link in news_links){
  html <- read_html(link)
  contents <- c(contents, html %>% html_nodes('#articleBodyContents') %>%
                  html_text())
}

#중복멘트제거 및 전처리
rm_flash <- 'flash 오류를 우회하기 위한 함수 추가function flashremoveCallback'

con_pre <- gsub('[\r\n\t]', '', contents) 
con_pre <- gsub('\\s+',' ',con_pre)
con_pre <- gsub('[[:cntrl:]]','',con_pre)
con_pre <- gsub('[[:punct:]]','',con_pre)
con_pre <- gsub('\\d+',' ',con_pre)
con_pre <- str_remove_all(con_pre, rm_flash)

#단어추출
library(KoNLP)
con <- extractNoun(con_pre)

# 자료집생성
library(tm)
contents_corpus <- Corpus(VectorSource(con))
contents_corpus
inspect(contents_corpus)


# 단어 선별(단어 길이 2개 이상)
# 단어길이 2개 이상인 단어만 선별하여 matrix 자료구조로 변경
contents_corpus <- tm_map(contents_corpus, removePunctuation) # 문장부호 제거
contents_term <- TermDocumentMatrix(contents_corpus, control=list(wordLengths=c(4,16)))
Encoding(contents_term$dimnames$Terms) = 'utf-8'
contents_term

# matrix 자료구조를 data.frame 자료구조로 변경
contents.df <- as.data.frame(as.matrix(contents_term)) 
dim(contents.df)
contents.df

# 단어 빈도수 구하기 - 빈도수가 높은 순서대로 내림차순 정렬
wordResult <- sort(rowSums(contents.df), decreasing=TRUE) # 빈도수로 내림차순 정렬
wordResult[1:10]

#각 플랫폼 별 언급 빈도 구하기
ottflats = list("넷플릭스", "왓챠", "티빙", "웨이브", "쿠팡플레이", "디즈니")
freqs <- NULL
for (x in ottflats){
  freqs <- c(freqs, wordResult[x])
}
names(freqs) <- ottflats
freqs <- sort(freqs, T)
graph <- barplot(freqs, names=names(freqs),main="국내 OTT 플랫폼 별 언론 언급 빈도수", col=rainbow(6),
        border="white", beside=T, cex.main=1.0,cex.lab=1.0, ylim=c(0,500))
text(x=graph,y=freqs,labels=freqs,pos=3,col="black")

# 단어 구름(wordcloud) 생성 - 디자인 적용 전
library(wordcloud)
myName <- names(wordResult) # 단어 이름 생성 -> 빈도수의 이름 
wordcloud(myName) # 단어구름 적성

# 단어 구름에 디자인 적용(빈도수, 색상, 위치, 회전 등) 
# 단어이름과 빈도수로 data.frame 생성
word.df <- data.frame(word=myName, freq=wordResult) 
str(word.df) # word, freq 변수

# 단어 색상과 글꼴 지정
pal <- brewer.pal(12,"Paired") # 12가지 색상 pal <- brewer.pal(9,"Set1") # Set1~ Set3
# 폰트 설정세팅 : "맑은 고딕", "서울남산체 B"
windowsFonts(malgun=windowsFont("맑은 고딕"))  #windows

# 단어 구름 시각화 - 별도의 창에 색상, 빈도수, 글꼴, 회전 등의 속성 적용 
#x11( ) # 별도의 창을 띄우는 함수
wordcloud(word.df$word, word.df$freq, 
          scale=c(5,1), min.freq=3, random.order=F, 
          rot.per=.1, colors=pal, family="malgun",max.words = 85)
