/*********************************************************************
 * bcm63xxx machine driver.c -- ALSA SoC machine driver for BCM963xxx/476xxx board 
 *
 * Author: Kevin Li <kevin-ke.li@broadcom.com>
 * 
 * Copyright (c) 2018 Broadcom Corporation
 * All Rights Reserved
 *
 * <:label-BRCM:2018:DUAL/GPL:standard
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 ********************************************************************/
#include <linux/module.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>

#define SCLK_BIT_PER_CHANNEL   32
#define MCLK_RATIO             ( params_rate(params)<=48000 ? 8 : 1)
#define MCLK_RATIO_FACTOR      2

static int bcm63xxx_hw_params(struct snd_pcm_substream *substream,
                            struct snd_pcm_hw_params *params)
{
   int ret = 0;
   unsigned int MClk; 
   struct snd_soc_pcm_runtime *rtd = substream->private_data;
   struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
   struct snd_soc_dai *codec_dai = rtd->codec_dai;

   /* Set the AP DAI configuration */
   ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_I2S   | 
                                      SND_SOC_DAIFMT_NB_NF |
                                      SND_SOC_DAIFMT_CBS_CFS);
   if (ret < 0)
   {
      return ret;
   }

   MClk = params_rate(params)*SCLK_BIT_PER_CHANNEL*2*MCLK_RATIO*MCLK_RATIO_FACTOR;

   ret = snd_soc_dai_set_sysclk(cpu_dai, 0, MClk, SND_SOC_CLOCK_OUT);
   if (ret < 0)
   {
      return ret;
   }
   /* set the codec system clock */
   ret = snd_soc_dai_set_sysclk(codec_dai, 0, MClk, SND_SOC_CLOCK_OUT);
   if (ret < 0)
   {
     return ret;
   }
   return 0;
}

#ifdef CONFIG_SND_SOC_MAPLELEAF
static int tlv320adc3101_hw_params(struct snd_pcm_substream *substream,
                                   struct snd_pcm_hw_params *params)
{
   int ret = 0;
   unsigned int MClk; 
   struct snd_soc_pcm_runtime *rtd = substream->private_data;
   struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
   struct snd_soc_dai *codec_dai = rtd->codec_dai;

   /* Set the AP DAI configuration */
   ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_I2S   | 
                                      SND_SOC_DAIFMT_NB_NF |
                                      SND_SOC_DAIFMT_CBS_CFS);
   if (ret < 0)
   {
      return ret;
   }

   MClk = params_rate(params)*SCLK_BIT_PER_CHANNEL*2*MCLK_RATIO*MCLK_RATIO_FACTOR;

   ret = snd_soc_dai_set_sysclk(cpu_dai, 0, MClk, SND_SOC_CLOCK_OUT);
   if (ret < 0)
   {
      return ret;
   }
   /* set the codec system clock */
   ret = snd_soc_dai_set_sysclk(codec_dai, 0, MClk, SND_SOC_CLOCK_OUT);
   if (ret < 0)
   {
     return ret;
   }
   return 0;
}

#endif

static struct snd_soc_ops bcm63xxx_ops = {
   .hw_params = bcm63xxx_hw_params,
};

#ifdef CONFIG_SND_SOC_MAPLELEAF
static struct snd_soc_ops tlv320adc3101_ops = {
   .hw_params = tlv320adc3101_hw_params,
};
#endif

static struct snd_soc_dai_link bcm63xx_soc_card_dai[] = 
{

#ifdef CONFIG_SND_SOC_CS4345
   {
      .name           = "bcm63158ref2", //This is chosen arbitrarily.  Can be anything.
      .stream_name    = "Playback",
      .codec_dai_name = "cs4345-hifi",
      .cpu_dai_name   = "squamish-cpu-dai",
#ifdef CONFIG_SND_BCM63xx_PCM_SQUAMISH
      .platform_name  = "ff860c00.bcm63xx-pcm",
#endif
#ifdef CONFIG_SND_BCM63xx_I2S_WHISTLER
      .platform_name  = "ff802080.bcm63xx-i2s",
#endif
      .codec_name     = "cs4345",
      .ops            = &bcm63xxx_ops,
      .dai_fmt 	      = (SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_I2S |
                         SND_SOC_DAIFMT_IB_NF),	
   },
#elif CONFIG_SND_SOC_MAPLELEAF
   {
      .name           = "MapleLeaf Speaker", //This is chosen arbitrarily.  Can be anything.
      .stream_name    = "Playback",
      .codec_dai_name = "tlv320dac3203-hifi",
      .cpu_dai_name   = "ff802080.bcm63xx-i2s",
      //.platform_name  = "bcm63xx-pcm-audio",
      .platform_name  = "ff802080.bcm63xx-i2s",
      .codec_name     = "tlv320dac3203.0-0018",
      .ops            = &bcm63xxx_ops,
      .dai_fmt 	      = (SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_I2S |
                         SND_SOC_DAIFMT_IB_NF),	
   },
   {
      .name           = "MapleLeaf Mic Array",
      .stream_name    = "Capture",
      .codec_dai_name = "tlv320adc3101-hifi",
      .cpu_dai_name   = "ff802080.bcm63xx-i2s",
      //.platform_name  = "bcm63xx-pcm-audio",
      .platform_name  = "ff802080.bcm63xx-i2s",
      .codec_name     = "tlv320adc3101.0-0019",
      .ops            = &tlv320adc3101_ops,
      .dai_fmt 	      = (SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_I2S |
                         SND_SOC_DAIFMT_IB_NF),	
   },
#endif

};

static struct snd_soc_card snd_soc_bcm63xx_SoundCard = 
{
#ifdef CONFIG_SND_SOC_CS4345
   .name      = "MapleTree",	
#elif CONFIG_SND_SOC_MAPLELEAF
   .name      = "MapleLeaf",	
#endif
   .owner     = THIS_MODULE,
   .dai_link  = bcm63xx_soc_card_dai,
   .num_links = ARRAY_SIZE(bcm63xx_soc_card_dai),
};

static struct platform_device *bcm63xx_snd_device;

static int __init bcm63xx_audio_init(void)
{
   int ret;

   bcm63xx_snd_device = platform_device_alloc("soc-audio", -1);
   if (!bcm63xx_snd_device)
   {
      return -ENOMEM;
   }

   platform_set_drvdata(bcm63xx_snd_device, &snd_soc_bcm63xx_SoundCard);
  
   ret = platform_device_add(bcm63xx_snd_device);
   if (ret)
   {
      platform_device_put(bcm63xx_snd_device);
   }

   return ret;
}
late_initcall(bcm63xx_audio_init);
static void __exit bcm63xx_audio_exit(void)
{
   platform_device_unregister(bcm63xx_snd_device);
}
module_exit(bcm63xx_audio_exit);

MODULE_AUTHOR("Kevin Li kevin-ke.li@broadcom.com");
MODULE_DESCRIPTION("ALSA SoC BCM 63153REF4D-bcm63xxx");
MODULE_LICENSE("GPL");
