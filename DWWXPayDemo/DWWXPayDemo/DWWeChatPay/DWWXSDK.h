//
//  DWWXPay.h
//  DWWXPayDemo
//
//  Created by 四海全球 on 2017/6/12.
//  Copyright © 2017年 dwang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WXApi.h"

typedef enum : NSUInteger {
    /** 微信支付 */
    DWWXPayMoney,
    /** 订单查询 */
    DWWXOrderquery
} DWWXRequestType;

typedef NS_ENUM(NSUInteger, DWWXOperatingResult) {
    /** 转入退款 */
    DWWXOrderqueryResultTypeRefund = 0,
    
    /** 未支付 */
    DWWXOrderqueryResultTypeNotPay,
    
    /** 交易已关闭 */
    DWWXOrderqueryResultTypeClosed,
    
    /** 已撤销（刷卡支付） */
    DWWXOrderqueryResultTypeRevoked,
    
    /** 用户支付中 */
    DWWXOrderqueryResultTypeUserPaying,
    
    /** 交易失败(其他原因，如银行返回失败) */
    DWWXOrderqueryResultTypePayFailed,
    
    /** 此交易订单号不存在,该API只能查提交支付交易返回成功的订单，请商户检查需要查询的订单号是否正确 */
    DWWXOrderqueryResultTypeNotExist,
    
    /** 系统错误，系统异常，请再调用发起查询 */
    DWWXOrderqueryResultTypeSystemError,
    
    /** 其它原因 */
    DWWXOrderqueryResultTypeUnknown,
    
    /** 用户点击取消并返回 */
    DWWXPayResultTypeCancel,
    
    /** 发送失败 */
    DWWXPayResultTypeSentFail,
    
    /** 普通错误类型 */
    DWWXPayResultTypeCommon,
    
    /** 授权失败 */
    DWWXPayResultTypeAuthDeny,
    
    /** 微信不支持 */
    DWWXPayResultTypeUnsupport,
    
    /** 其它原因 */
    DWWXPayResultTypeUnknown,
    
    /** 系统异常 */
    DWWXPayResultTypeSystemError
};

@interface DWWXSDK : NSObject<WXApiDelegate>

/** 支付成功的回调 */
typedef void (^DWWXOperatingSuccess)(BOOL success);
/** 错误回调 */
typedef void (^DWWXOperatingErrorResult)(DWWXOperatingResult operatingResult, NSString *error, NSString *errorMsg);
@property(nonatomic, copy) DWWXOperatingSuccess wxPayOperatingSuccess;
@property(nonatomic, copy) DWWXOperatingErrorResult wxOperatingErrorResult;


/**
 *  单例创建支付对象
 *
 */
+ (instancetype)wxSDK;

/**
 *  向微信终端程序注册第三方应用。
 *
 *  @param appid        微信开发者ID
 *  @param isEnableMTA  是否支持MTA数据上报
 *  @return 成功返回YES，失败返回NO。
 */
- (BOOL)dw_registerApp:(NSString *)appid enableMTA:(BOOL)isEnableMTA;

/**
 向微信终端程序注册第三方应用。

 @param appid 微信开发者ID
 @return 是否注册成功
 */
- (BOOL)dw_registerApp:(NSString *)appid;

/**
 获取付款需要的xml

 @param appid 微信开放平台审核通过的应用APPID
 @param mch_id 微信支付分配的商户号
 @param partnerKey 商户Key密钥/key设置路径：微信商户平台(pay.weixin.qq.com)-->账户设置-->API安全-->密钥设置
 @param body 商品描述
 @param out_trade_no 商户订单号
 @param total_fee 订单总金额，单位为分
 @param notify_url 接收微信支付异步通知回调地址，通知url必须为直接可访问的url，不能携带参数。
 @return xmlString
 */
- (NSString *)dw_obtainWXPayXmlAppid:(NSString *)appid mch_id:(NSString *)mch_id partnerKey:(NSString *)partnerKey body:(NSString *)body out_trade_no:(NSString *)out_trade_no total_fee:(int)total_fee notify_url:(NSString *)notify_url;

/**
 获取查询订单需要的xml

 @param appid 微信开放平台审核通过的应用APPID
 @param mch_id 微信支付分配的商户号
 @param partnerKey 商户Key密钥/key设置路径：微信商户平台(pay.weixin.qq.com)-->账户设置-->API安全-->密钥设置
 @param out_trade_no 商户订单号
 @return xmlString
 */
- (NSString *)dw_obtainWXQueryOrderXmlAppid:(NSString *)appid mch_id:(NSString *)mch_id partnerKey:(NSString *)partnerKey out_trade_no:(NSString *)out_trade_no;


/**
 调起支付/查询订单

 @param wxRequestType 操作类型
 @param xmlString 发送的xml数据
 @param success 成功
 @param result 失败
 */
- (void)dw_wxRequestType:(DWWXRequestType)wxRequestType xmlString:(NSString *)xmlString success:(DWWXOperatingSuccess)success result:(DWWXOperatingErrorResult)result;
/** 检查是否安装微信 */
+ (BOOL)dw_isWXAppInstalled;

/** 判断当前微信的版本是否支持OpenApi */
+ (BOOL)dw_isWXAppSupportApi;

/** 获取微信的itunes安装地址 */
+ (NSString *)dw_getWXAppInstallUrl;

/** 获取当前微信SDK的版本号 */
+ (NSString *)dw_getApiVersion;

@end


@interface DWWeChatModel : NSObject

/**
 *  此字段是通信标识，非交易标识，交易是否成功需要查看result_code来判断
 *  SUCCESS/FAIL
 */
@property (copy, nonatomic) NSString *return_code;

/**
 *  返回信息，如非空，为错误原因
 *  签名失败
 *  参数格式校验错误
 */
@property (copy, nonatomic) NSString *return_msg;

/**
 *  应用APPID
 */
@property (copy, nonatomic) NSString *appid;

/**
 *  商户号
 */
@property (copy, nonatomic) NSString *mch_id;

/**
 *  设备号，
 */
@property (copy, nonatomic) NSString *device_info;

/**
 *  随机字符串
 */
@property (copy, nonatomic) NSString *nonce_str;

/**
 *  签名
 */
@property (copy, nonatomic) NSString* sign;

/**
 *  业务结果
 */
@property (copy, nonatomic) NSString *result_code;

/**
 *  错误代码
 */
@property (copy, nonatomic) NSString *err_code;

/**
 *  错误代码描述
 */
@property (copy, nonatomic) NSString *err_code_des;

/**
 *  交易类型
 */
@property (copy, nonatomic) NSString *trade_type;

/**
 *  预支付交易会话标识
 */
@property (copy, nonatomic) NSString *prepay_id;

/**
 *  交易状态
 */
@property (copy, nonatomic) NSString *trade_state;
- (instancetype)initWithDictionary:(NSDictionary *)dict;
+ (instancetype)weChatModelWithDictionary:(NSDictionary *)dict;
@end

@interface NSString (Extension)
/** md5 一般加密 */
+ (NSString *)dw_md5String:(NSString *)string;

/** 获取随机数 */
+ (NSString *)dw_obtainRandomNumber;

/** 获取IP地址 */
+ (NSString *)dw_obtainIPAddress;

/** 获取付款XML字符串 */
+ (NSString *)dw_obtainWXPayXmlAppid:(NSString *)appid mch_id:(NSString *)mch_id nonce_str:(NSString *)nonce_str sign:(NSString *)sign body:(NSString *)body out_trade_no:(NSString *)out_trade_no total_fee:(int)total_fee spbill_create_ip:(NSString *)spbill_create_ip notify_url:(NSString *)notify_url trade_type:(NSString *)trade_type;

/** 获取查询订单XML字符串 */
+ (NSString *)dw_obtainWXQueryOrderXmlAppid:(NSString *)appid mch_id:(NSString *)mch_id nonce_str:(NSString *)nonce_str out_trade_no:(NSString *)out_trade_no sign:(NSString *)sign;
@end

