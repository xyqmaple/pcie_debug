/**
 * @file pci_debug.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _PCI_DEBUG_H_
#define _PCI_DEBUG_H_

#include <stdint.h>
#include <endian.h>
#include <sys/mman.h>

#define pr_err		printf
#define pr_info		printf
#define pr_debug	printf

/* PCI device */
typedef struct {
	/* Base address region */
	unsigned int bar;

	/* Slot info */
	unsigned int domain;
	unsigned int bus;
	unsigned int slot;
	unsigned int function;

	/* Resource filename */
	char         filename[100];

	/* File descriptor of the resource */
	int          fd;

	/* Memory mapped resource */
	unsigned char *maddr;
	unsigned int   size;
	unsigned int   offset;

	/* PCI physical address */
	unsigned int   phys;

	/* Address to pass to read/write (includes offset) */
	unsigned char *addr;
} device_t;

static inline uint8_t read_8(device_t *dev, uint32_t offset)
{
	return *(volatile uint8_t *)(dev->addr + offset);
}

static inline void write_8(device_t *dev, uint32_t offset, uint8_t data)
{
	*(volatile uint8_t *)(dev->addr + offset) = data;
	msync((void *)(dev->addr + offset), 1, MS_SYNC | MS_INVALIDATE);
}

static inline uint16_t read_le16(device_t *dev, uint32_t offset)
{
	uint16_t data = *(volatile uint16_t *)(dev->addr + offset);

#if (__BYTE_ORDER == __BIG_ENDIAN)
	data = bswap_16(data);
#endif
	return data;
}

static inline void write_le16(device_t *dev, uint32_t offset, uint16_t data)
{
#if (__BYTE_ORDER == __BIG_ENDIAN)
	data = bswap_16(data);
#endif
	*(volatile uint16_t *)(dev->addr + offset) = data;
	msync((void *)(dev->addr + offset), 2, MS_SYNC | MS_INVALIDATE);
}

static inline uint16_t read_be16(device_t *dev, uint32_t offset)
{
	uint32_t data = *(volatile uint16_t *)(dev->addr + offset);
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
	data = bswap_16(data);
#endif
	return data;
}

static inline void write_be16(device_t *dev, uint32_t offset, uint16_t data)
{
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
	data = bswap_16(data);
#endif
	*(volatile uint16_t *)(dev->addr + offset) = data;
	msync((void *)(dev->addr + offset), 2, MS_SYNC | MS_INVALIDATE);
}

static inline uint32_t read_le32(device_t *dev, uint32_t offset)
{
	uint32_t data = *(volatile uint32_t *)(dev->addr + offset);

#if (__BYTE_ORDER == __BIG_ENDIAN)
	data = bswap_32(data);
#endif
	return data;
}

static inline void write_le32(device_t *dev, uint32_t offset, uint32_t data)
{
#if (__BYTE_ORDER == __BIG_ENDIAN)
	data = bswap_32(data);
#endif
	*(volatile uint32_t *)(dev->addr + offset) = data;
	msync((void *)(dev->addr + offset), 4, MS_SYNC | MS_INVALIDATE);
}

static inline uint32_t read_be32(device_t *dev, uint32_t offset)
{
	uint32_t data = *(volatile uint32_t *)(dev->addr + offset);

#if (__BYTE_ORDER == __LITTLE_ENDIAN)
	data = bswap_32(data);
#endif
	return data;
}

static inline void write_be32(device_t *dev, uint32_t offset, uint32_t data)
{
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
	data = bswap_32(data);
#endif
	*(volatile uint32_t *)(dev->addr + offset) = data;
	msync((void *)(dev->addr + offset), 4, MS_SYNC | MS_INVALIDATE);
}

#endif /* !_PCI_DEBUG_H_ */
