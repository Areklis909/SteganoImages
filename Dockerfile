
FROM areklis909/boost-docker:0.0.1 as boost
FROM areklis909/opencv-docker:0.0.1

RUN apt-get -y update \
    && apt-get -y install ntp build-essential wget git curl zip unzip  \
    && rm -rf /var/lib/apt/lists/*

ENV BOOST_LIB_DIR  /usr/local/lib
ENV TARGET_LIB_DIR /usr/lib/x86_64-linux-gnu

RUN rm -rf /usr/include/boost/program_options/*

COPY --from=boost ${BOOST_LIB_DIR}/libboost_program_options.* ${TARGET_LIB_DIR}/
COPY --from=boost /usr/local/include/boost/program_options /usr/include/boost/program_options/

ENV APP SteganoImages

RUN mkdir $APP

COPY . $APP

ENV BUILD_FOLDER build_stegano

RUN mkdir $BUILD_FOLDER && cd $BUILD_FOLDER && cmake ../${APP} \
    && make && rm -rf ${APP} && rm -r ../SteganoImages 


