#ifndef _COMPAT_LINUX_NETDEVICE_H
#define _COMPAT_LINUX_NETDEVICE_H 1

#include "../../compat/config.h"

#include_next <linux/netdevice.h>

#ifndef SET_ETHTOOL_OPS
#define SET_ETHTOOL_OPS(netdev,ops) \
    ( (netdev)->ethtool_ops = (ops) )
#endif

#if !defined(HAVE_NETDEV_EXTENDED_HW_FEATURES)     && \
    !defined(HAVE_NETDEV_OPS_EXT_NDO_FIX_FEATURES) && \
    !defined(HAVE_NETDEV_OPS_EXT_NDO_SET_FEATURES) && \
    !defined(HAVE_NDO_SET_FEATURES)
#define LEGACY_ETHTOOL_OPS
#endif

#ifndef NETDEV_BONDING_INFO
#define NETDEV_BONDING_INFO     0x0019
#endif


#ifndef HAVE_NETDEV_MASTER_UPPER_DEV_GET_RCU
#define netdev_master_upper_dev_get_rcu(x) (x)->master
#endif

#ifndef HAVE_NETIF_KEEP_DST
/* This device needs to keep skb dst for qdisc enqueue or ndo_start_xmit() */
static inline void netif_keep_dst(struct net_device *dev)
{
	/* IFF_XMIT_DST_RELEASE_PERM   = 1<<17 */
	dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | (1<<17) );
}
#endif

#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 18)
#ifdef HAVE_ALLOC_ETHERDEV_MQ
#ifndef HAVE_NETIF_SET_REAL_NUM_TX_QUEUES
static inline void netif_set_real_num_tx_queues(struct net_device *netdev,
						unsigned int txq)
{
	netdev->real_num_tx_queues = txq;
}
#endif
#endif
#endif /* LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 18) */

#ifndef HAVE_NETDEV_RSS_KEY_FILL
static inline void netdev_rss_key_fill(void *addr, size_t len)
{
	__be32 *hkey;

	hkey = (__be32 *)addr;
	hkey[0] = cpu_to_be32(0xD181C62C);
	hkey[1] = cpu_to_be32(0xF7F4DB5B);
	hkey[2] = cpu_to_be32(0x1983A2FC);
	hkey[3] = cpu_to_be32(0x943E1ADB);
	hkey[4] = cpu_to_be32(0xD9389E6B);
	hkey[5] = cpu_to_be32(0xD1039C2C);
	hkey[6] = cpu_to_be32(0xA74499AD);
	hkey[7] = cpu_to_be32(0x593D56D9);
	hkey[8] = cpu_to_be32(0xF3253C06);
	hkey[9] = cpu_to_be32(0x2ADC1FFC);
}
#endif

#ifndef NAPI_POLL_WEIGHT
/* Default NAPI poll() weight
 * Device drivers are strongly advised to not use bigger value
 */
#define NAPI_POLL_WEIGHT 64
#endif

#ifndef NETDEV_JOIN
#define NETDEV_JOIN           0x0014
#endif

#ifndef NETDEV_MASTER_UPPER_DEV_LINK_4_PARAMS
#define netdev_master_upper_dev_link(a,b,c,d) netdev_master_upper_dev_link(a,b)
#endif

#ifdef HAVE_ALLOC_NETDEV_MQS_6_PARAMS
#define alloc_netdev_mqs(a, b, c, d, e) alloc_netdev_mqs(a, b, NET_NAME_UNKNOWN, c, d, e)
#endif

#ifdef alloc_netdev_mq
#undef alloc_netdev_mq
#define alloc_netdev_mq(sizeof_priv, name, setup, count) \
    alloc_netdev_mqs(sizeof_priv, name, setup, count, count)
#endif

#ifdef alloc_netdev
#undef alloc_netdev
#define alloc_netdev(sizeof_priv, name, name_assign_type, setup) \
	alloc_netdev_mqs(sizeof_priv, name, setup, 1, 1)
#endif

#ifndef HAVE_NETIF_TRANS_UPDATE
/* legacy drivers only, netdev_start_xmit() sets txq->trans_start */
static inline void netif_trans_update(struct net_device *dev)
{
	struct netdev_queue *txq = netdev_get_tx_queue(dev, 0);

	if (txq->trans_start != jiffies)
		txq->trans_start = jiffies;
}
#endif

#ifdef HAVE_REGISTER_NETDEVICE_NOTIFIER_RH
#define register_netdevice_notifier register_netdevice_notifier_rh
#define unregister_netdevice_notifier unregister_netdevice_notifier_rh
#endif

#ifndef HAVE_NETDEV_NOTIFIER_INFO_TO_DEV
#define netdev_notifier_info_to_dev LINUX_BACKPORT(netdev_notifier_info_to_dev)
static inline struct net_device *
netdev_notifier_info_to_dev(void *ptr)
{
	return (struct net_device *)ptr;
}
#endif

#endif	/* _COMPAT_LINUX_NETDEVICE_H */
