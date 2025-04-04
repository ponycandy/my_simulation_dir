#ifndef MAPPATHITEM_H
#define MAPPATHITEM_H

#include "GraphicsMapLib_global.h"
#include <QGraphicsPathItem>
#include <QGeoCoordinate>
#include <QPen>
#include <QVector>
#include <QSet>
class MapObjectItem;

/*!
 * \brief 航路
 * \note 航路类将负责航点的生命周期
 */
class GRAPHICSMAPLIB_EXPORT MapPathItem : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    using QGraphicsPathItem::setPen;
    using QGraphicsPathItem::pen;

    MapPathItem();
    ~MapPathItem();
    /// 设置路径绑定的路网
    void AddRoadMapEdge( int real_id,double jd,double wd,int Id,QString type);
    /// 设置鼠标可移动航点
    void setMoveable(bool movable);
    /// 设置航点可选中
    void setCheckable(bool checkable);
    /// 设置航点被选中
    void setChecked(int index, bool checked = true);
    void setChecked(MapObjectItem *point, bool checked = true);
    /// 切换航点选中状态
    void toggle(int index);
    void toggle(MapObjectItem *point);
    /// 设置航点选中互斥性
    void setExclusive(bool exclusive);
    /// 设置编辑状态和非编辑状态下两种画笔
    void setPen(bool editable, const QPen &pen);
    /// 获取画笔
    QPen pen(bool editable) const;
    /// 添加航点
    MapObjectItem *append(MapObjectItem *point);
    MapObjectItem *append(const QGeoCoordinate &coord);
    /// 插入航点
    MapObjectItem *insert(const int &index, MapObjectItem *point);
    MapObjectItem *insert(const int &index, const QGeoCoordinate &coord);
    /// 替换航点
    MapObjectItem *replace(const int &index, MapObjectItem *point);
    MapObjectItem *replace(const int &index, const QGeoCoordinate &coord);
    /// 删除航点
    void remove(int index);
    void remove(MapObjectItem *point);
    /// 设置航点
    const QVector<MapObjectItem*> &setPoints(const QVector<MapObjectItem*> &points);
    /// 获取航点列表
    const QVector<MapObjectItem*> &points() const;
    /// 获取所有选中的航点
    QVector<MapObjectItem*> checked() const;
    /// 获取所有选中的航点下标
    QVector<int> checkedIndex() const;
    /// 获取下标
    int indexOf(MapObjectItem *point);

public:
    /// 获取所有的实例
    static const QSet<MapPathItem*> &items();

signals:
    void added(const int &index, const MapObjectItem *point);
    void removed(const int &index);
    void updated(const int &index, const MapObjectItem *point);
    void changed();

private:
    static QSet<MapPathItem*> m_items;         ///< 所有实例

private:
    void updatePolyline();
    void updatePointMoved();
    void updatePointPressed();
    void updatePointReleased();
    void bindPoint(MapObjectItem *point);

private:
    QPen m_normalPen;    ///< 非编辑状态画笔
    QPen m_moveablePen;  ///< 编辑状态画笔
    bool m_moveable;     ///< 航点可移动
    bool m_checkable;    ///< 航点可选中性
    bool m_exclusive;    ///< 航点选中互斥性
    //
    QVector<MapObjectItem*> m_points;               ///< 航点元素
    QVector<std::tuple<int, double, double,int,QString>> road_edges; ///< 路网元素
    bool                    m_lastPointIsChecked;   ///< 上次触发按钮的选中状态
};

#endif // MAPROUTEITEM_H
