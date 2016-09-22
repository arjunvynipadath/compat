#ifndef LINUX_3_12_COMPAT_H
#define LINUX_3_12_COMPAT_H

#include <linux/version.h>
#include <../../compat/config.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,12,0))

#ifndef PTR_ERR_OR_ZERO
#define PTR_ERR_OR_ZERO(p) PTR_RET(p)
#endif

#define MODULE_ALIAS_FS(NAME) MODULE_ALIAS("fs-" NAME)

#define file_inode LINUX_BACKPORT(file_inode)
static inline struct inode *file_inode(struct file *f)
{
	return f->f_dentry->d_inode;
}

#include <linux/pci.h>

#ifndef HAVE_PCIE_LINK_WIDTH
/* These values come from the PCI Express Spec */
enum pcie_link_width {
	PCIE_LNK_WIDTH_RESRV	= 0x00,
	PCIE_LNK_X1		= 0x01,
	PCIE_LNK_X2		= 0x02,
	PCIE_LNK_X4		= 0x04,
	PCIE_LNK_X8		= 0x08,
	PCIE_LNK_X12		= 0x0C,
	PCIE_LNK_X16		= 0x10,
	PCIE_LNK_X32		= 0x20,
	PCIE_LNK_WIDTH_UNKNOWN  = 0xFF,
};
#endif

extern const unsigned char pcie_link_speed[];

#ifndef HAVE_PCIE_GET_MINIMUM_LINK
#define pcie_get_minimum_link LINUX_BACKPORT(pcie_get_minimum_link)
int pcie_get_minimum_link(struct pci_dev *dev, enum pci_bus_speed *speed,
		enum pcie_link_width *width);
#endif
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3,12,0)) */
#endif /* LINUX_3_12_COMPAT_H */
