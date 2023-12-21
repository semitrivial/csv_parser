FROM gcr.io/oss-fuzz-base/base-builder
RUN apt-get update && apt-get install -y make autoconf automake libtool

COPY . $SRC/csv_parser
COPY .clusterfuzzlite/build.sh $SRC/build.sh
WORKDIR $SRC/csv_parser