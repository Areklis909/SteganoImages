FROM httpd:2.4

RUN apt-get -y update && apt-get -y install wget \
    cmake python3 python3-pip unzip qt5-default \
    && rm -rf /var/lib/apt/lists/*

ENV BOOST_DIR boost_1_67_0

ENV BOOST_ARCHIVE $BOOST_DIR.tar.gz

RUN wget https://dl.bintray.com/boostorg/release/1.67.0/source/$BOOST_ARCHIVE \ 
    && tar -zxvf $BOOST_ARCHIVE && cd $BOOST_DIR \
    && ./bootstrap.sh --with-libraries=program_options && ./b2 install \
    && cd ../ && rm -r $BOOST_DIR $BOOST_ARCHIVE


ENV APP SteganoImages

RUN mkdir $APP

COPY . $APP

ENV OPENCV_SCRIPT prepare_environment.sh

ENV BUILD_FOLDER build_stegano

ENV SOURCE_CODE_FOLDER SteganoImages

RUN cd $APP && sh $OPENCV_SCRIPT && rm -r opencv-* && cd ../ \
    && mkdir $BUILD_FOLDER && cd $BUILD_FOLDER && cmake ../${SOURCE_CODE_FOLDER} \
    && make



