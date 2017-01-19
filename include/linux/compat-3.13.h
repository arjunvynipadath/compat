#ifndef LINUX_3_13_COMPAT_H
#define LINUX_3_13_COMPAT_H

#include <linux/version.h>
#include <linux/completion.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,13,0))

#include <linux/sched/prio.h>

#ifndef HAVE_REINIT_COMPLETION
#define HAVE_REINIT_COMPLETION

static inline void reinit_completion(struct completion *x)
{
	x->done = 0;
}

#endif

#define pcie_get_mps LINUX_BACKPORT(pcie_get_mps)
int pcie_get_mps(struct pci_dev *dev);

#define pcie_set_mps LINUX_BACKPORT(pcie_set_mps)
int pcie_set_mps(struct pci_dev *dev, int mps);

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3,13,0)) */

#endif /* LINUX_3_13_COMPAT_H */
