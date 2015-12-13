/*
 * md5加密函数
*/

QString md5String(const QString& sourceStr) {//MD5加密
    QString md5String;

    QByteArray bb;
    bb = QCryptographicHash::hash(sourceStr.toLatin1(), QCryptographicHash::Md5);
    md5String.append(bb.toHex());

    return md5String;
}