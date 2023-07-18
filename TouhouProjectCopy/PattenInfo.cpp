#include "stdafx.h"
#include "rapidcsv.h"

bool PattenInfo::LoadFromFile(const std::string path)
{
    rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
    id = doc.GetCell <std::string>(0, 1);

    for (int i = 4; i < doc.GetRowCount(); ++i)
    {
        auto rows = doc.GetRow<float>(i);
        bulletAction.push_back({ (BulletInfoType)rows[0], rows[1] });
    }
    return true;
}