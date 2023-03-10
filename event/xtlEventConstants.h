
#ifndef XTLEVENTCONSTANTS_H
#define XTLEVENTCONSTANTS_H

#include <QString>

#include "xtlPluginFrameworkExport.h"

/**
 * \ingroup EventAdmin
 *
 * Defines standard names for <code>xtlEventHandler</code> and Qt event slot properties.
 *
 * \see xtlEventHandler
 * \see xtlEventAdmin::subscribeSlot()
 */
struct XTL_PLUGINFW_EXPORT xtlEventConstants {

  /**
   * Registration property (named <code>event.topics</code>)
   * specifying the <code>xtlEvent</code> topics of interest to an Event Handler
   * (a service object or a subscribed slot).
   * <p>
   * Event handlers SHOULD be registered with this property. The value of the
   * property is a QString or a QStringList that describes the topics in
   * which the handler is interested. An asterisk ('*') may be used as a
   * trailing wildcard. Event handlers which do not have a value for this
   * property must not receive events. More precisely, the value of each
   * string must conform to the following grammar:
   *
   * <pre>
   *  topic-description := '*' | topic ( '&#47*' )?
   *  topic := token ( '/' token )*
   * </pre>
   *
   * @see xtlEvent
   */
  static const QString EVENT_TOPIC; // = "event.topics"

  /**
   * Registration property (named <code>event.filter</code>)
   * specifying a filter to further select <code>xtlEvent</code> s of interest to
   * an Event Handler (a service object or a subscribed slot).
   * <p>
   * Event handlers MAY be registered with this property. The value of this
   * property is a QString containing an LDAP-style filter specification. Any
   * of the event's properties may be used in the filter expression. Each
   * event handler is notified for any event which belongs to the topics in
   * which the handler has expressed an interest. If the event handler is also
   * registered with this property, then the properties of the event
   * must also match the filter for the event to be delivered to the event handler.
   * <p>
   * If the filter syntax is invalid, then the Event Handler must be ignored
   * and a warning should be logged.
   *
   * @see xtlEvent
   * @see xtlLDAPSearchFilter
   */
  static const QString EVENT_FILTER; // = "event.filter"

  /**
   * Service Registration property specifying the delivery qualities requested
   * by an Event Handler service.
   * <p>
   * Event handlers MAY be registered with this property. Each value of this
   * property is a string specifying a delivery quality for the Event handler.
   *
   * <p>
   * The value of this property must be of type <code>QString</code> or
   * <code>QStringList</code>.
   *
   * @see #DELIVERY_ASYNC_ORDERED
   * @see #DELIVERY_ASYNC_UNORDERED
   */
  static const QString EVENT_DELIVERY; // = "event.delivery"

  /**
   * Event Handler delivery quality value specifying the Event Handler
   * requires asynchronously delivered events be delivered in order. Ordered
   * delivery is the default for asynchronously delivered events.
   *
   * <p>
   * This delivery quality value is mutually exclusive with
   * {@link #DELIVERY_ASYNC_UNORDERED}. However, if both this value and
   * {@link #DELIVERY_ASYNC_UNORDERED} are specified for an event handler,
   * this value takes precedence.
   *
   * @see #EVENT_DELIVERY
   */
  static const QString DELIVERY_ASYNC_ORDERED; // = "async.ordered"

  /**
   * Event Handler delivery quality value specifying the Event Handler does
   * not require asynchronously delivered events be delivered in order. This
   * may allow an Event Admin implementation to optimize asynchronous event
   * delivery by relaxing ordering requirements.
   *
   * <p>
   * This delivery quality value is mutually exclusive with
   * {@link #DELIVERY_ASYNC_ORDERED}. However, if both this value and
   * {@link #DELIVERY_ASYNC_ORDERED} are specified for an event handler,
   * {@link #DELIVERY_ASYNC_ORDERED} takes precedence.
   *
   * @see #EVENT_DELIVERY
   */
  static const QString DELIVERY_ASYNC_UNORDERED; // = "async.unordered"

  /**
   * The Plugin Symbolic Name of the plugin relevant to the event. The type of
   * the value for this event property is <code>QString</code>.
   */
  static const QString PLUGIN_SYMBOLICNAME; // = "plugin.symbolicName"

  /**
   * The Plugin id of the plugin relevant to the event. The type of the value
   * for this event property is <code>long</code>.
   */
  static const QString PLUGIN_ID; // = "plugin.id"

  /**
   * The xtlPlugin object of the plugin relevant to the event. The type of the
   * value for this event property is <code>QSharedPointer<xtlPlugin></code>.
   */
  static const QString PLUGIN; // = "plugin"

  /**
   * The version of the plugin relevant to the event. The type of the value
   * for this event property is {@link xtlVersion}.
   */
  static const QString PLUGIN_VERSION; // = "plugin.version"

  /**
   * The forwarded event object. Used when rebroadcasting an event that was
   * sent via some other event mechanism. The type of the value for this event
   * property depends on the event topic (for org/xtal/PluginEvent/&0x42; the
   * the type will be xtlPluginEvent).
   */
  static const QString EVENT; // = "event"

  /**
   * An exception or error. The type of the value for this event property is
   * <code>xtlRuntimeException</code>.
   */
  static const QString EXCEPTION; // = "exception"

  /**
   * The name of the exception type. Must be equal to the name of the class of
   * the exception in the event property {@link #EXCEPTION}. The type of the
   * value for this event property is <code>QString</code>.
   */
  static const QString EXCEPTION_CLASS; // = "exception.class"

  /**
   * The exception message. Must be equal to the result of calling
   * <code>what()</code> on the exception in the event property
   * {@link #EXCEPTION}. The type of the value for this event property is
   * <code>QString</code>.
   */
  static const QString EXCEPTION_MESSAGE; // = "exception.message"

  /**
   * A human-readable message that is usually not localized. The type of the
   * value for this event property is <code>QString</code>.
   */
  static const QString MESSAGE; // = "message"

  /**
   * A service reference. The type of the value for this event property is
   * {@link xtlServiceReference}.
   */
  static const QString SERVICE; // = "service"

  /**
   * A service's id. The type of the value for this event property is
   * <code>long</code>.
   */
  static const QString SERVICE_ID; // = xtlPluginConstants::SERVICE_ID

  /**
   * A service's objectClass. The type of the value for this event property is
   * <code>QStringList</code>.
   */
  static const QString SERVICE_OBJECTCLASS; // = "service.objectClass"

  /**
   * A service's persistent identity. The type of the value for this event
   * property is <code>QString</code>.
   */
  static const QString SERVICE_PID; // = xtlPluginConstants::SERVICE_PID

  /**
   * The time when the event occurred, as reported by
   * <code>QDateTime::currentDateTime()</code>. The type of the value for this
   * event property is <code>QDateTime</code>.
   */
  static const QString TIMESTAMP; // = "timestamp"

};

#endif // XTLEVENTCONSTANTS_H
